from datetime import timedelta
from vaf import vafpy, BaseTypes

from .imported_models import *

app_module1 = vafpy.ApplicationModule(name="AppModule1", namespace="demo")
app_module1.add_consumed_interface(instance_name="HvacStatusConsumer", interface=interfaces.Nsprototype.Nsserviceinterface.Nshvacstatus.hvac_status)
app_module1.add_provided_interface(instance_name="DataExchangeProvider", interface=interfaces.Demo.data_exchange_interface)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
app_module1.add_task(task=periodic_task)
