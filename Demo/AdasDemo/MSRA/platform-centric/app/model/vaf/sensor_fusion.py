from datetime import timedelta
from vaf import vafpy, BaseTypes

# Import the CaC support from platform derive or interface import
from .imported_models import *

sensor_fusion = vafpy.ApplicationModule(name="SensorFusion", namespace="NsApplicationUnit::NsSensorFusion")

# Add consumed and provided interfaces using the ApplicationModule API
sensor_fusion.add_provided_interface(
    "ObjectDetectionListModule", interfaces.Adas.Interfaces.object_detection_list_interface
)
sensor_fusion.add_consumed_interface("ImageServiceConsumer1", interfaces.Af.AdasDemoApp.Services.image_service)
sensor_fusion.add_consumed_interface("ImageServiceConsumer2", interfaces.Af.AdasDemoApp.Services.image_service)
sensor_fusion.add_consumed_interface(
    "SteeringAngleServiceConsumer", interfaces.Af.AdasDemoApp.Services.steering_angle_service
)
sensor_fusion.add_consumed_interface("VelocityServiceConsumer", interfaces.Af.AdasDemoApp.Services.velocity_service)
periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
sensor_fusion.add_task(task=periodic_task)
