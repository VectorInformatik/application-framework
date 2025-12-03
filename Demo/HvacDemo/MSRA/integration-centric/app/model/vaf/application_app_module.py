from datetime import timedelta
from vaf import vafpy, BaseTypes

# TODO: Import the CaC support from platform derive or interface import
# from .msra import *
# from .imported_models import *

application_app_module = vafpy.ApplicationModule(
    name="ApplicationAppModule", namespace="demo"
)

hvac_control_service = vafpy.ModuleInterface(name="HvacControl", namespace="demo")
hvac_control_service.add_data_element(name="CompressorState", datatype=BaseTypes.STRING)
hvac_control_service.add_data_element(name="ValvePosition", datatype=BaseTypes.STRING)
hvac_control_service.add_data_element(name="FanSpeed", datatype=BaseTypes.STRING)
hvac_control_service.add_operation(
    name="ChangeTemperature",
    in_parameter={"Value": BaseTypes.UINT8_T},
)

hvac_status_service = vafpy.ModuleInterface(name="HvacStatus", namespace="demo")
hvac_status_service.add_data_element(name="CompressorStatus", datatype=BaseTypes.STRING)
hvac_status_service.add_data_element(name="ValveStatus", datatype=BaseTypes.STRING)
hvac_status_service.add_data_element(name="FanRightSpeed", datatype=BaseTypes.STRING)
hvac_status_service.add_data_element(name="FanLeftSpeed", datatype=BaseTypes.STRING)
hvac_status_service.add_operation(
    name="SetDegree",
    in_parameter={"Value": BaseTypes.UINT8_T},
)

application_app_module.add_consumed_interface(
    instance_name="AppHvacStatusConsumer", interface=hvac_status_service
)
application_app_module.add_provided_interface(
    instance_name="AppHvacControlProvider", interface=hvac_control_service
)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
application_app_module.add_task(task=periodic_task)
