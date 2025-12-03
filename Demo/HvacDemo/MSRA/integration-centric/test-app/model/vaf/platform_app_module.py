from datetime import timedelta
from vaf import vafpy, BaseTypes

# TODO: Import the CaC support from platform derive or interface import
from .msra import *
# from .imported_models import *

platform_app_module = vafpy.ApplicationModule(
    name="PlatformAppModule", namespace="demo"
)
# TODO: Add consumed and provided interfaces using the ApplicationModule API
# e.g. platform_app_module.add_consumed_interface(instance_name="AccelerationProvider", interface=msra.Acceleration)

platform_app_module.add_consumed_interface(
    instance_name="HvacControlConsumer",
    interface=Nsprototype.Nsserviceinterface.Nshvaccontrol.hvac_control,
)
platform_app_module.add_provided_interface(
    instance_name="HvacStatusProvider",
    interface=Nsprototype.Nsserviceinterface.Nshvacstatus.hvac_status,
)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
platform_app_module.add_task(task=periodic_task)
