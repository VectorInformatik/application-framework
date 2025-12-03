from datetime import timedelta

from .application_modules import *
from vaf import *

from .msra import *

HvacPlatform.executable.add_application_module(AppModule3, [])

HvacPlatform.executable.connect_consumed_interface_to_platform(
    AppModule3,
    Instances.AppModule3.ConsumedInterfaces.HvacControlConsumer,
    HvacPlatform.ConsumerModules.hvac_control,
)
HvacPlatform.executable.connect_provided_interface_to_platform(
    AppModule3,
    Instances.AppModule3.ProvidedInterfaces.HvacStatusProvider,
    HvacPlatform.ProviderModules.hvac_status,
)
