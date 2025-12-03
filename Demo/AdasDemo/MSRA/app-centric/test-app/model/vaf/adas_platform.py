from datetime import timedelta

from .application_modules import *
from vaf import *

# TODO: Import the CaC support depending on your middleware to have access to platform interfaces, modules, and executables
# from .msra import *

adas_platform_app = Executable("adas_platform_app", timedelta(milliseconds=20))

adas_platform_app.add_application_module(MsraPlatform, [])

# connect middleware interfaces
adas_platform_app.connect_provided_interface_to_msra(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.ImageServiceProvider1,
    "ImageService1",
    vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
    tcp_port = 1025,
    udp_port = 1025
)
adas_platform_app.connect_provided_interface_to_msra(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.ImageServiceProvider2,
    "ImageService2",
    vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
    tcp_port = 1026,
    udp_port = 1026
)
adas_platform_app.connect_provided_interface_to_msra(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.SteeringAngleServiceProvider,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)
adas_platform_app.connect_provided_interface_to_msra(
    MsraPlatform,
    Instances.MsraPlatform.ProvidedInterfaces.VelocityServiceProvider,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)

adas_platform_app.connect_consumed_interface_to_msra(
    MsraPlatform,
    Instances.MsraPlatform.ConsumedInterfaces.BrakeServiceConsumer,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)

