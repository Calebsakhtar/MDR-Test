import os

rootpath = os.path.dirname(os.path.abspath(__file__))

ip_path = os.path.join(rootpath,'MATLAB_OP.csv')
ip_file = open(ip_path, 'r')
lines = ip_file.readlines()
ip_file.close()

op_path = os.path.join(rootpath,'designs.csv')
op_file = open(op_path,'w')

var_names = 'L_D,M_empty,MTOW,Stall\n'
op_file.write(var_names)

var_name_list = var_names.split(',')
minimize_str = ''
for i in range(len(var_name_list)-1):
    minimize_str += "TRUE,"
minimize_str += 'TRUE\n'

op_file.write(minimize_str)
op_file.writelines(lines)
op_file.close()
