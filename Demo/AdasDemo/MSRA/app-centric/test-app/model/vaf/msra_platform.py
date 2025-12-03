from datetime import timedelta
from vaf import vafpy, BaseTypes

# TODO: Import the CaC support from platform derive or interface import
# from .msra import *
from .imported_models import *

msra_platform = vafpy.ApplicationModule(name="MsraPlatform", namespace="NsApplicationUnit::NsMsraPlatform")

msra_platform.add_consumed_interface("BrakeServiceConsumer", interfaces.Af.AdasDemoApp.Services.brake_service)
msra_platform.add_provided_interface("ImageServiceProvider1", interfaces.Af.AdasDemoApp.Services.image_service)
msra_platform.add_provided_interface("ImageServiceProvider2", interfaces.Af.AdasDemoApp.Services.image_service)
msra_platform.add_provided_interface("SteeringAngleServiceProvider", interfaces.Af.AdasDemoApp.Services.steering_angle_service)
msra_platform.add_provided_interface("VelocityServiceProvider", interfaces.Af.AdasDemoApp.Services.velocity_service)

periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
msra_platform.add_task(task=periodic_task)
