from datetime import timedelta
from vaf import vafpy, BaseTypes

from .imported_models import *

app_module2 = vafpy.ApplicationModule(name="AppModule2", namespace="demo")
app_module2.add_consumed_interface(instance_name="DataExchangeConsumer", interface=interfaces.Demo.data_exchange_interface)
app_module2.add_provided_interface(instance_name="HvacControlProvider", interface=interfaces.Nsprototype.Nsserviceinterface.Nshvaccontrol.hvac_control)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
app_module2.add_task(task=periodic_task)
