#User area, you can edit to adapt with your project, please read Readme.txt before edit here
#(1) Path of a folder contains genenated code.
import os
directory_gen = os.path.abspath(__file__)

# directory_gen = "D:\\Work\\Gitlab\\DLMS_v2_Skeleton_1P\\1p\\rl78i1c (256)\\Source\\rl78i1c\\application\\dlms2"
#(2) Update subfolder level of project, 
#This follow layout folder in CS+ project
#It may be different from your storage folder.
#So, please take a look CS+ tree code before setting under code.
dlms_code_project_tree = ["application","dlms2"]
#End user area, do not edit below code please

classes_generated = list()
objects_generated = list()
libwrapper_generated = list()
usercode_generated = list()
comlibwrapper_generated = list()

classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_classes.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_classes.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class01.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class01.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class03.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class03.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class04.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class04.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class07.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class07.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class08.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class08.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class09.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class09.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class15.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class15.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class18.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class18.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class20.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class20.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class22.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class22.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class23.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class23.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class40.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class40.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class41.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class41.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class45.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class45.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class48.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class48.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class64.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class64.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class70.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class70.c")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class71.h")
classes_generated.append(directory_gen + "\\codegen\\classes\\r_dlms_class71.c")

objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class01.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class03.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class04.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class07.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class08.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class09.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class15.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class18.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class20.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class22.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class23.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class40.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class41.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class45.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class48.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class64.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class70.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_object_class71.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_objects.c")
objects_generated.append(directory_gen + "\\codegen\\objects\\r_dlms_objects.h")

libwrapper_generated.append(directory_gen + "\\codegen\\libwrapper\\r_dlms_cosem_aes_gcm_wrapper.c")
libwrapper_generated.append(directory_gen + "\\codegen\\libwrapper\\r_dlms_malloc_wrapper.c")
libwrapper_generated.append(directory_gen + "\\codegen\\libwrapper\\r_dlms_physical_wrapper.c")
libwrapper_generated.append(directory_gen + "\\codegen\\libwrapper\\r_dlms_timeout_wrapper.c")
libwrapper_generated.append(directory_gen + "\\codegen\\libwrapper\\r_dlms_wrapper_conversion_ip.c")
libwrapper_generated.append(directory_gen + "\\codegen\\libwrapper\\r_dlms_wrapper_conversion_ip.h")

usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class01.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class01.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class03.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class03.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class04.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class04.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class07.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class07.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class08.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class08.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class09.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class09.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class15.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class15.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class18.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class18.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class20.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class20.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class22.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class22.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class40.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class40.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class41.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class41.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class45.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class45.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class48.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class48.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class64.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class64.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class70.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class70.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class71.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_usercode_class71.c")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_user.h")
usercode_generated.append(directory_gen + "\\usercode\\r_dlms_user.c")

comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_com_wrapper_config.h")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_dummy.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_ethernet_serial_rx65n.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_fibocom_h310.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_fibocom_h310.h")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_interface.h")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_raw.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_tcp_wrapper_usrtcp232.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_udp_wrapper_dummy.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_udp_wrapper_ethernet_serial_rx65n.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_udp_wrapper_fibocom_h310.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_udp_wrapper_interface.h")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_udp_wrapper_nuratech_wisun.c")
comlibwrapper_generated.append(directory_gen + "\\usercode\\com_libwrapper\\r_dlms_udp_wrapper_raw.c")

classes_existed = list()
objects_existed = list()
libwrapper_existed = list()
usercode_existed = list()
comlibwrapper_existed = list()
list_files = list()
list_files = project.File.Information()
print("")
#create list existed files
for fileNamepath in list_files:
	x = "r_dlms_class" in fileNamepath
	y = "r_dlms_object_class" in fileNamepath
	z = "\libwrapper" in fileNamepath
	k = "r_dlms_usercode_class" in fileNamepath
	r = "usercode\com_libwrapper" in fileNamepath
	if x == True:
		classes_existed.append(fileNamepath)
	if y == True:
		objects_existed.append(fileNamepath)
	if z == True:
		libwrapper_existed.append(fileNamepath)
	if k == True:
		usercode_existed.append(fileNamepath)
	if r == True:
		comlibwrapper_existed.append(fileNamepath)
#Prepare filter
#For class
cl_gen_set = set(classes_generated)
cl_exis_set = set(classes_existed)
#For object
obj_gen_set = set(objects_generated)
obj_exis_set = set(objects_existed)
#For libwrapper
libwr_gen_set = set(libwrapper_generated)
libwr_exis_set = set(libwrapper_existed)
#For usercode
user_gen_set = set(usercode_generated)
user_exis_set = set(usercode_existed)
#For com lib wrapper
comlibwrapper_gen_set = set(comlibwrapper_generated)
comlibwrapper_exis_set = set(comlibwrapper_existed)
#Make list superflous files
#for class
class_remove = list(cl_gen_set.union(cl_exis_set) - cl_gen_set.intersection(cl_exis_set) - cl_gen_set)
class_add = list(cl_gen_set.union(cl_exis_set) - cl_gen_set.intersection(cl_exis_set) - cl_exis_set)
#for object
object_remove = list(obj_gen_set.union(obj_exis_set) - obj_gen_set.intersection(obj_exis_set) - obj_gen_set)
object_add = list(obj_gen_set.union(obj_exis_set) - obj_gen_set.intersection(obj_exis_set) - obj_exis_set)
#for libwapper
libwapper_remove = list(libwr_gen_set.union(libwr_exis_set) - libwr_gen_set.intersection(libwr_exis_set) - libwr_gen_set)
libwapper_add = list(libwr_gen_set.union(libwr_exis_set) - libwr_gen_set.intersection(libwr_exis_set) - libwr_exis_set)
#for usercode
usercode_remove = list(user_gen_set.union(user_exis_set) - user_gen_set.intersection(user_exis_set) - user_gen_set)
usercode_add = list(user_gen_set.union(user_exis_set) - user_gen_set.intersection(user_exis_set) - user_exis_set)
#for comlibwrapper
comlibwrapper_remove = list(comlibwrapper_gen_set.union(comlibwrapper_exis_set) - comlibwrapper_gen_set.intersection(comlibwrapper_exis_set) - comlibwrapper_gen_set)
comlibwrapper_add = list(comlibwrapper_gen_set.union(comlibwrapper_exis_set) - comlibwrapper_gen_set.intersection(comlibwrapper_exis_set) - comlibwrapper_exis_set)

#remove superflous files
print("remove")
#for class
for super_flous_class in class_remove:
	print(super_flous_class)
	project.File.Remove(super_flous_class)
print("")
#for object
for super_flous_object in object_remove:
	print(super_flous_object)
	project.File.Remove(super_flous_object)
print("")
#for libwrp
for super_flous_libwrp in libwapper_remove:
	print(super_flous_libwrp)
	project.File.Remove(super_flous_libwrp)
print("")
#for usercode
for super_flous_user in usercode_remove:
    kk = "usercode\r_dlms" in super_flous_user
    if kk == True:
        print(super_flous_user)
        project.File.Remove(super_flous_user)
print("")
#for comlibwrapper
#for super_flous_comlibwrapper in comlibwrapper_remove:
#	print(super_flous_comlibwrapper)
#	project.File.Remove(super_flous_comlibwrapper)

#add missed files
print("")
#super_flous_user
print("Add")
#for class
for add_class in class_add:
	print(add_class)
	project.File.Add(add_class, dlms_code_project_tree + ["codegen","classes"])
#for object
print("")
for add_object in object_add:
	print(add_object)
	project.File.Add(add_object, dlms_code_project_tree + ["codegen","objects"])
#for libwrp
print("")
for add_libwrp in libwapper_add:
	print(add_libwrp)
	project.File.Add(add_libwrp, dlms_code_project_tree + ["codegen", "libwrapper"])
#for usercode
print("")
for add_user in usercode_add:
	print(add_user)
	project.File.Add(add_user, dlms_code_project_tree + ["usercode"])
#for comlibwrapper
print("")
for add_comlibwrapper in comlibwrapper_generated:
	print(add_comlibwrapper)
	project.File.Add(add_comlibwrapper, dlms_code_project_tree + ["usercode", "com_libwrapper"])

print("DLMS library update")
pathLibRemove = directory_gen + "\\library\\" + "DLMS Library v2.2.lib"
pathLibAdd = directory_gen + "\\library\\" + "DLMS Library v2.3.lib"
print("remove old lib")
project.File.Remove(pathLibRemove)
print("add new lib")
project.File.Add(pathLibAdd, dlms_code_project_tree + ["library"])