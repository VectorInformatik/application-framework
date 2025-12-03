from datetime import timedelta

from .application_modules import *
from vaf import *

# Import the CaC support depending on your middleware to have access to platform interfaces, modules, and executables
from .msra import *

# Add application modules to executable instances
AdasApplication.executable.add_application_module(SensorFusion, [])
AdasApplication.executable.add_application_module(CollisionDetection, [])

# Wire the internal application module instances
AdasApplication.executable.connect_interfaces(
    SensorFusion,
    Instances.SensorFusion.ProvidedInterfaces.ObjectDetectionListModule,
    CollisionDetection,
    Instances.CollisionDetection.ConsumedInterfaces.ObjectDetectionListModule,
)

# Connect application modules with platform or platform modules (lower layer abstraction modules)
AdasApplication.executable.connect_consumed_interface_to_platform(
    SensorFusion,
    Instances.SensorFusion.ConsumedInterfaces.ImageServiceConsumer1,
    AdasApplication.ConsumerModules.r_port_image_service1,
)
AdasApplication.executable.connect_consumed_interface_to_platform(
    SensorFusion,
    Instances.SensorFusion.ConsumedInterfaces.ImageServiceConsumer2,
    AdasApplication.ConsumerModules.r_port_image_service2,
)
AdasApplication.executable.connect_consumed_interface_to_platform(
    SensorFusion,
    Instances.SensorFusion.ConsumedInterfaces.SteeringAngleServiceConsumer,
    AdasApplication.ConsumerModules.r_port_steering_angle_service,
)
AdasApplication.executable.connect_consumed_interface_to_platform(
    SensorFusion,
    Instances.SensorFusion.ConsumedInterfaces.VelocityServiceConsumer,
    AdasApplication.ConsumerModules.r_port_velocity_service,
)

AdasApplication.executable.connect_provided_interface_to_platform(
    CollisionDetection,
    Instances.CollisionDetection.ProvidedInterfaces.BrakeServiceProvider,
    AdasApplication.ProviderModules.p_port_brake_service,
)
