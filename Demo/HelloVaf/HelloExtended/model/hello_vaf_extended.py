from datetime import timedelta

from vaf import vafmodel, Executable

from .application_modules import Instances, AppModule2, AppModule1, AppModule3
from vaf import *

# TODO: Import the CaC support depending on your middleware to have access to platform interfaces, modules, and executables
# from msra import *

# --------------------------------------------------------------------------------------------------------------------------
#  Executable definitions
# --------------------------------------------------------------------------------------------------------------------------
executable1 = Executable("DemoExecutable")

# Add application modules to executable1 instances
executable1.add_application_module(AppModule1, [])
executable1.add_application_module(AppModule2, [])

# Connect the internal application module instances
executable1.connect_interfaces(
    AppModule1,
    Instances.AppModule1.ProvidedInterfaces.AppProviderIC,
    AppModule2,
    Instances.AppModule2.ConsumedInterfaces.AppConsumerIC,
)

executable1.connect_provided_interface_to_msra(
    AppModule1,
    Instances.AppModule1.ProvidedInterfaces.MSRAProviderIPC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.IPC,
)
executable1.connect_provided_interface_to_msra(
    AppModule1,
    Instances.AppModule1.ProvidedInterfaces.MSRAProviderSOMEIP,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)
executable1.connect_provided_interface_to_msra(
    AppModule1,
    Instances.AppModule1.ProvidedInterfaces.MSRAProviderZC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.ZERO_COPY,
)

executable1.connect_consumed_interface_to_msra(
    AppModule2,
    Instances.AppModule2.ConsumedInterfaces.MSRAConsumerIPC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.IPC,
)
executable1.connect_consumed_interface_to_msra(
    AppModule2,
    Instances.AppModule2.ConsumedInterfaces.MSRAConsumerSOMEIP,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)
executable1.connect_consumed_interface_to_msra(
    AppModule2,
    Instances.AppModule2.ConsumedInterfaces.MSRAConsumerZC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.ZERO_COPY,
)

# Create executable2
executable2 = Executable("TestExecutable")

executable2.add_application_module(AppModule3, [])

executable2.connect_consumed_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ConsumedInterfaces.MSRAConsumerIPC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.IPC,
)
executable2.connect_consumed_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ConsumedInterfaces.MSRAConsumerSOMEIP,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)
executable2.connect_consumed_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ConsumedInterfaces.MSRAConsumerZC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.ZERO_COPY,
)

executable2.connect_provided_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ProvidedInterfaces.MSRAProviderIPC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.IPC,
)
executable2.connect_provided_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ProvidedInterfaces.MSRAProviderSOMEIP,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.SOME_IP,
)
executable2.connect_provided_interface_to_msra(
    AppModule3,
    Instances.AppModule3.ProvidedInterfaces.MSRAProviderZC,
    deployment_type=vafmodel.MSRAConnectionPointDeploymentType.ZERO_COPY,
)
