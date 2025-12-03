from datetime import timedelta

from .application_modules import PlatformAppModule, Instances
from vaf import *

# TODO: Import the CaC support depending on your middleware to have access to platform interfaces, modules, and executables
from .msra import *

HvacPlatform.executable.add_application_module(PlatformAppModule, [])

HvacPlatform.executable.connect_consumed_interface_to_platform(
    PlatformAppModule,
    Instances.PlatformAppModule.ConsumedInterfaces.HvacControlConsumer,
    HvacPlatform.ConsumerModules.hvac_control,
)
HvacPlatform.executable.connect_provided_interface_to_platform(
    PlatformAppModule,
    Instances.PlatformAppModule.ProvidedInterfaces.HvacStatusProvider,
    HvacPlatform.ProviderModules.hvac_status,
)
