from datetime import timedelta

from .application_modules import *
from vaf import *

from .msra import *

HvacExecutable.executable.add_application_module(AppModule1, [])
HvacExecutable.executable.add_application_module(AppModule2, [])

HvacExecutable.executable.connect_interfaces(AppModule1, Instances.AppModule1.ProvidedInterfaces.DataExchangeProvider,
                                             AppModule2, Instances.AppModule2.ConsumedInterfaces.DataExchangeConsumer)

HvacExecutable.executable.connect_consumed_interface_to_platform(
    AppModule1,
    Instances.AppModule1.ConsumedInterfaces.HvacStatusConsumer,
    HvacExecutable.ConsumerModules.hvac_status,
)
HvacExecutable.executable.connect_provided_interface_to_platform(
    AppModule2,
    Instances.AppModule2.ProvidedInterfaces.HvacControlProvider,
    HvacExecutable.ProviderModules.hvac_control,
)
