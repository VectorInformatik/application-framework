from datetime import timedelta
from vaf import vafpy, BaseTypes

# TODO: Import the CaC support from platform derive or interface import
from .msra import *
# from .imported_models import *

msra_platform = vafpy.ApplicationModule(name="MsraPlatform", namespace="NsApplicationUnit::NsMsraPlatform")

# TODO: Add consumed and provided interfaces using the ApplicationModule API
msra_platform.add_consumed_interface("BrakeServiceConsumer", Af.AdasDemoApp.Services.brake_service)
msra_platform.add_provided_interface("ImageServiceProvider1", Af.AdasDemoApp.Services.image_service)
msra_platform.add_provided_interface("ImageServiceProvider2", Af.AdasDemoApp.Services.image_service)
msra_platform.add_provided_interface("SteeringAngleServiceProvider", Af.AdasDemoApp.Services.steering_angle_service)
msra_platform.add_provided_interface("VelocityServiceProvider", Af.AdasDemoApp.Services.velocity_service)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
msra_platform.add_task(task=periodic_task)
