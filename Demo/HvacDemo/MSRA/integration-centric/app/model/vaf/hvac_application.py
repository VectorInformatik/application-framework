from .application_modules import TransformerAppModule, Instances, ApplicationAppModule
from vaf import *

# TODO: Import the CaC support depending on your middleware to have access to platform interfaces, modules, and executables
from msra import *

HvacApplication.executable.add_application_module(TransformerAppModule, [])
HvacApplication.executable.add_application_module(ApplicationAppModule, [])

HvacApplication.executable.connect_interfaces(
    TransformerAppModule,
    Instances.TransformerAppModule.ProvidedInterfaces.AppHvacStatusProvider,
    ApplicationAppModule,
    Instances.ApplicationAppModule.ConsumedInterfaces.AppHvacStatusConsumer,
)

HvacApplication.executable.connect_interfaces(
    ApplicationAppModule,
    Instances.ApplicationAppModule.ProvidedInterfaces.AppHvacControlProvider,
    TransformerAppModule,
    Instances.TransformerAppModule.ConsumedInterfaces.AppHvacControlConsumer,
)

HvacApplication.executable.connect_consumed_interface_to_platform(
    TransformerAppModule,
    Instances.TransformerAppModule.ConsumedInterfaces.PlatformHvacStatusConsumer,
    HvacApplication.ConsumerModules.hvac_status,
)
HvacApplication.executable.connect_provided_interface_to_platform(
    TransformerAppModule,
    Instances.TransformerAppModule.ProvidedInterfaces.PlatformHvacControlProvider,
    HvacApplication.ProviderModules.hvac_control,
)
