#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import datetime
import os
import shutil
import sys

import yaml
from pprint import pprint

from common import common, gen_control_func, gen_report_func


def gen_control_node(protocol, send_fmt_val):
    # ���ƽڵ������д
    # protocol ����canID�ģ�yaml����
    # include_msgsName_list = list()
    
    message_name = protocol["name"]
    
    send_fmt_val["include_msgsName_list"] += \
            "".join('#include "pix_driver_msgs/%s.h"\n'%(message_name))
            
    send_fmt_val["include_ParseName_list"] += \
            "".join('#include "%s.hpp"\n'%(message_name))
            
    send_fmt_val["global_variable_ros_msg"] += \
            "".join("static can_msgs::Frame can_%s;\n"%(message_name.split("_",1)[0]))
            
    send_fmt_val["global_variable_vehicle_msg"] += \
            "".join("static pix_driver_msgs::%s %s_msg;\n"%(message_name, message_name))
            
    send_fmt_val["global_variable_sendEntity"] += \
            "".join("static %s %s_entity;\n"%(message_name.replace('_', '').capitalize(), message_name))
            
    send_fmt_val["global_variable_Enable"] += \
            "".join("%s_enable, "%(message_name.split("_",1)[0]))
            
    send_fmt_val["global_variable_sendTimeStamp"] += \
            "".join("%s_prev_t=0, "%(message_name.split("_",1)[0]))
            
    send_fmt_val["sendCanID_callback_func_list"] += gen_control_func.sendCanID_callback_func_list(protocol)
            
    send_fmt_val["if_canID_prev_t"] += gen_control_func.timer_callback_func(protocol)
            
    send_fmt_val["gen_Subscriber_list"] +=  gen_control_func.gen_Subscriber_list(protocol)


def gen_report_node(canId_recv_nameInfo, recv_fmt_val):
    # recv_fmt_val   
    # canId_nameInfo ���õ��� canId_nameInfo["report"] 
    for i in canId_recv_nameInfo:
        recv_fmt_val["include_pixMsgs_list"] += '#include "pix_driver_msgs/{name}.h"\n'.format(name=i[0])
        recv_fmt_val["include_hpp_list"] += '#include "{name}.hpp"\n'.format(name=i[0])
        # print(i[0].rsplit('_', 1))
        recv_fmt_val["global_variable_Publisher_list"] += "static ros::Publisher pub_{can_name};\n".format(can_name=i[0].rsplit('_', 1)[0])
        
        recv_fmt_val["global_variable_pixmsg"] +=  "static pix_driver_msgs::{name} {name}_msg;\n".format(name=i[0], can_name=i[0].rsplit('_', 1)[0])
        
        recv_fmt_val["global_variable_recvEntity"] += "static {name2}  {name}_entity;\n"\
            .format(name2=i[0].replace('_', '').capitalize(), name=i[0])
            
        recv_fmt_val["if_recv_canId"] += gen_report_func.can_callback_if(i)
        
        recv_fmt_val["Publisher_include"] += 'pub_{can_name} = nh.advertise<pix_driver_msgs::{name}>("/pix/{can_name}", 1, true);\n\t'\
            .format(name=i[0], can_name=i[0].rsplit('_', 1)[0])



def gen_protocols(protocol_conf_file, protocol_dir):
    # ����yaml�ļ�������c++ ros��������
    # protocol_conf_file yaml�ļ�·�� 
    # protocol_dir       ���ɵĴ�����·��  
    
    print("Generating canID node cpp")
    # �жϴ��·���Ƿ����
    if not os.path.exists(protocol_dir):
        os.makedirs(protocol_dir)
        
    # ��ȡyaml�ļ����� �� yaml����-content
    with open(protocol_conf_file, 'r') as fp:
        content = yaml.safe_load(fp)
        
    protocols = content["protocols"]
    # car_type = content["car_type"]
    # ģ����������ʣ�
    send_tmplate = ["include_msgsName_list", "include_ParseName_list", \
                    "global_variable_vehicle_msg", "global_variable_ros_msg", "global_variable_sendEntity",  \
                    "global_variable_Enable",  "global_variable_sendTimeStamp", \
                    "sendCanID_callback_func_list", "if_canID_prev_t",\
                    "gen_Subscriber_list"]
    recv_template = ["include_pixMsgs_list", "include_hpp_list", "global_variable_Publisher_list", \
                    "global_variable_pixmsg", "global_variable_recvEntity", \
                    "if_recv_canId", "Publisher_include"]
    
    
    send_fmt_val = {}
    recv_fmt_val = {}
    canId_nameInfo = {}  # �洢canId������
    canId_nameInfo["report"] = list()
    canId_nameInfo["control"] = list()
    # ��ʼ��
    for i in  send_tmplate:
        send_fmt_val[i] = ""       
    for i in  recv_template:
        recv_fmt_val[i] = ""
    
    
    for p_name in protocols:
        # print(p_name)
        protocol = protocols[p_name]

        # �����·������ϴ�- ������Ӧ����
        if protocol["protocol_type"] == "report":
            # gen_report_node(protocol, recv_fmt_val)
            canId_nameInfo["report"].append([protocol["name"], [i["name"] for i in protocol["vars"]] ])
            # canId_name.append(protocol)
        elif protocol["protocol_type"] == "control":
            canId_nameInfo["control"].append([protocol["name"], [i for i in protocol["vars"]]])
            gen_control_node(protocol, send_fmt_val)
        else:
            print("Unknown protocol_type:%s" % protocol["protocol_type"])
    else:
        send_fmt_val["global_variable_Enable"] = send_fmt_val["global_variable_Enable"][:-2] + ";"
        send_fmt_val["global_variable_sendTimeStamp"] = send_fmt_val["global_variable_sendTimeStamp"][:-2] + ";"
            
    # pprint(canId_nameInfo["report"][0][1])   
    gen_report_node(canId_nameInfo["report"], recv_fmt_val)
    # ���ɱ����ļ�
    # gen_build_file(car_type, protocol_dir)
    
    # ��ȡģ�����ݲ�����
    control_cpp_tpl_file = "template/control_node.cc.tpl"
    control_cpp_file = protocol_dir + "pix_driver/src/command_node.cc"
    control_FMT = common.get_tpl_fmt(control_cpp_tpl_file)
    with open(control_cpp_file, 'w') as fp:
        fp.write(control_FMT % send_fmt_val)
    
    report_cpp_tpl_file = "template/report_node.cc.tpl"
    report_cpp_file = protocol_dir + "pix_driver/src/report_node.cc"
    report_FMT = common.get_tpl_fmt(report_cpp_tpl_file)
    with open(report_cpp_file, 'w') as fp:
        fp.write(report_FMT % recv_fmt_val)   
        
     
    
    

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\npython %s some_config.yml" % sys.argv[0])
        sys.exit(0)
        
    with open(sys.argv[1], 'r') as fp:
        conf = yaml.safe_load(fp)
        
    protocol_conf = conf["protocol_conf"]
    # protocol_dir = conf["output_cpp_dir"] 
    output_dir = conf["output_dir"]
     
    # �ݹ�ɾ���ļ�����������
    shutil.rmtree(output_dir, True)
    os.makedirs(output_dir)
    # generate protocols
    gen_protocols(protocol_conf, "output/src/")
    
    
        
    