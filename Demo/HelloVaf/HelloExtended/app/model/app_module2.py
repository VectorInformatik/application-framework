from datetime import timedelta
from vaf import vafpy, BaseTypes

# TODO: Import the CaC support from platform derive or interface import
# from .msra import *
# from .imported_models import *

app_module2 = vafpy.ApplicationModule(name="AppModule2", namespace="demo")
# TODO: Add consumed and provided interfaces using the ApplicationModule API
# e.g. app_module2.add_consumed_interface(instance_name="AccelerationProvider", interface=msra.Acceleration)

ic_data_string = vafpy.ModuleInterface(name="ICDataInterfaceSTRING", namespace="ic_string")
ic_data_string.add_data_element("ICDataSTRING", datatype=BaseTypes.STRING)
app_module2.add_consumed_interface("AppConsumerIC", ic_data_string)

zc_data_int8 = vafpy.ModuleInterface(name="ZCDataInterfaceINT8", namespace="zc_int8")
zc_data_int8.add_data_element("ZCDataINT8", datatype=BaseTypes.INT8_T)
app_module2.add_consumed_interface("MSRAConsumerZC", zc_data_int8)

ipc_data_int8 = vafpy.ModuleInterface(name="IPCDataInterfaceINT8", namespace="ipc_int8")
ipc_data_int8.add_data_element("IPCDataINT8", datatype=BaseTypes.INT8_T)
app_module2.add_consumed_interface("MSRAConsumerIPC", ipc_data_int8)

someip_data_int8 = vafpy.ModuleInterface(name="SOMEIPDataInterfaceINT8", namespace="someip_int8")
someip_data_int8.add_data_element("SOMEIPDataINT8", datatype=BaseTypes.INT8_T)
app_module2.add_consumed_interface("MSRAConsumerSOMEIP", someip_data_int8)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
app_module2.add_task(task=periodic_task)
