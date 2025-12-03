from datetime import timedelta
from vaf import vafpy, BaseTypes

from .imported_models import *

app_module3 = vafpy.ApplicationModule(name="AppModule3", namespace="demo")
app_module3.add_consumed_interface(instance_name="HvacControlConsumer", interface=interfaces.Nsprototype.Nsserviceinterface.Nshvaccontrol.hvac_control)
app_module3.add_provided_interface(instance_name="HvacStatusProvider", interface=interfaces.Nsprototype.Nsserviceinterface.Nshvacstatus.hvac_status)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
app_module3.add_task(task=periodic_task)
