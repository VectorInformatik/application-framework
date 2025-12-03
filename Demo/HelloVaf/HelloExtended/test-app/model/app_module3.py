from datetime import timedelta
from vaf import vafpy, BaseTypes

# TODO: Import the CaC support from platform derive or interface import
# from .msra import *
# from .imported_models import *

app_module3 = vafpy.ApplicationModule(name="AppModule3", namespace="demo")
# TODO: Add consumed and provided interfaces using the ApplicationModule API
# e.g. app_module3.add_consumed_interface(instance_name="AccelerationProvider", interface=msra.Acceleration)

zc_data_uint8 = vafpy.ModuleInterface(name="ZCDataInterfaceUINT8", namespace="zc_uint8")
zc_data_uint8.add_data_element("ZCDataUINT8", datatype=BaseTypes.UINT8_T)
app_module3.add_consumed_interface("MSRAConsumerZC", zc_data_uint8)

ipc_data_uint8 = vafpy.ModuleInterface(name="IPCDataInterfaceUINT8", namespace="ipc_uint8")
ipc_data_uint8.add_data_element("IPCDataUINT8", datatype=BaseTypes.UINT8_T)
app_module3.add_consumed_interface("MSRAConsumerIPC", ipc_data_uint8)

someip_data_uint8 = vafpy.ModuleInterface(name="SOMEIPDataInterfaceUINT8", namespace="someip_uint8")
someip_data_uint8.add_data_element("SOMEIPDataUINT8", datatype=BaseTypes.UINT8_T)
app_module3.add_consumed_interface("MSRAConsumerSOMEIP", someip_data_uint8)

zc_data_int8 = vafpy.ModuleInterface(name="ZCDataInterfaceINT8", namespace="zc_int8")
zc_data_int8.add_data_element("ZCDataINT8", datatype=BaseTypes.INT8_T)
app_module3.add_provided_interface("MSRAProviderZC", zc_data_int8)

ipc_data_int8 = vafpy.ModuleInterface(name="IPCDataInterfaceINT8", namespace="ipc_int8")
ipc_data_int8.add_data_element("IPCDataINT8", datatype=BaseTypes.INT8_T)
app_module3.add_provided_interface("MSRAProviderIPC", ipc_data_int8)

someip_data_int8 = vafpy.ModuleInterface(name="SOMEIPDataInterfaceINT8", namespace="someip_int8")
someip_data_int8.add_data_element("SOMEIPDataINT8", datatype=BaseTypes.INT8_T)
app_module3.add_provided_interface("MSRAProviderSOMEIP", someip_data_int8)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
app_module3.add_task(task=periodic_task)
