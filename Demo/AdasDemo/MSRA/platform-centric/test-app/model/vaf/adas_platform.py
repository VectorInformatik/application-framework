from datetime import timedelta

from .application_modules import *
from vaf import *

# TODO: Import the CaC support depending on your middleware to have access to platform interfaces, modules, and executables
from .msra import *

AdasPlatform.executable.add_application_module(MsraPlatform, [])

AdasPlatform.executable.connect_provided_interface_to_platform(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.ImageServiceProvider1,
    AdasPlatform.ProviderModules.p_port_image_service1,
)
AdasPlatform.executable.connect_provided_interface_to_platform(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.ImageServiceProvider2,
    AdasPlatform.ProviderModules.p_port_image_service2,
)
AdasPlatform.executable.connect_provided_interface_to_platform(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.VelocityServiceProvider,
    AdasPlatform.ProviderModules.p_port_velocity_service,
)
AdasPlatform.executable.connect_provided_interface_to_platform(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.SteeringAngleServiceProvider,
    AdasPlatform.ProviderModules.p_port_steering_angle_service,
)

AdasPlatform.executable.connect_consumed_interface_to_platform(
    MsraPlatform,
    Instances.MsraPlatform.ConsumedInterfaces.BrakeServiceConsumer,
    AdasPlatform.ConsumerModules.r_port_brake_service,
)
