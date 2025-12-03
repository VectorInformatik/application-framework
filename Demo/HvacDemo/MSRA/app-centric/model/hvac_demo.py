from datetime import timedelta

from .application_modules import *
from vaf import *

# Create Hvac executable
HvacExecutable = Executable("hvac_app", timedelta(milliseconds=20))
HvacExecutable.add_application_module(AppModule1, [("PeriodicTask", timedelta(milliseconds=1), 0)])
HvacExecutable.add_application_module(AppModule2, [("PeriodicTask", timedelta(milliseconds=1), 1)])

HvacExecutable.connect_interfaces(
    AppModule1,
    Instances.AppModule1.ProvidedInterfaces.DataExchangeProvider,
    AppModule2,
    Instances.AppModule2.ConsumedInterfaces.DataExchangeConsumer
)

HvacExecutable.connect_consumed_interface_to_msra(
    AppModule1,
    Instances.AppModule1.ConsumedInterfaces.HvacStatusConsumer,
    subscription_type=vafmodel.MSRASubscriptionStrategy.LAZY,
)
HvacExecutable.connect_provided_interface_to_msra(
    AppModule2,
    Instances.AppModule2.ProvidedInterfaces.HvacControlProvider
)

# Create TestHvacExecutable
TestHvacExecutable = Executable("test_hvac_app", timedelta(milliseconds=20))

TestHvacExecutable.add_application_module(AppModule3, [])

TestHvacExecutable.connect_consumed_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ConsumedInterfaces.HvacControlConsumer,
    subscription_type=vafmodel.MSRASubscriptionStrategy.LAZY,
)
TestHvacExecutable.connect_provided_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ProvidedInterfaces.HvacStatusProvider
)
