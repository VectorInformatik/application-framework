from datetime import timedelta
from vaf import vafpy, BaseTypes

# Import the CaC support from platform derive or interface import
from .imported_models import *

collision_detection = vafpy.ApplicationModule(
    name="CollisionDetection", namespace="NsApplicationUnit::NsCollisionDetection"
)
# Add consumed and provided interfaces using the ApplicationModule API
collision_detection.add_provided_interface("BrakeServiceProvider", interfaces.Af.AdasDemoApp.Services.brake_service)
collision_detection.add_consumed_interface(
    "ObjectDetectionListModule", interfaces.Adas.Interfaces.object_detection_list_interface
)


periodic_task = vafpy.Task(name="PeriodicTask", period=timedelta(milliseconds=200))
collision_detection.add_task(task=periodic_task)
