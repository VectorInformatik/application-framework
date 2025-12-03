from vaf import BaseTypes, vafpy


hvac_control_service = vafpy.ModuleInterface(name="HvacControl", namespace="nsprototype::nsserviceinterface::nshvaccontrol")
hvac_control_service.add_data_element(name="CompressorState", datatype=BaseTypes.UINT8_T)
hvac_control_service.add_data_element(name="ValvePosition", datatype=BaseTypes.UINT8_T)
hvac_control_service.add_data_element(name="FanSpeed", datatype=BaseTypes.UINT8_T)
hvac_control_service.add_operation(
    name="ChangeTemperature",
    in_parameter={"Value": BaseTypes.UINT8_T},
)

hvac_status_service = vafpy.ModuleInterface(name="HvacStatus", namespace="nsprototype::nsserviceinterface::nshvacstatus")
hvac_status_service.add_data_element(name="CompressorStatus", datatype=BaseTypes.UINT32_T)
hvac_status_service.add_data_element(name="ValveStatus", datatype=BaseTypes.UINT32_T)
hvac_status_service.add_data_element(name="FanRightSpeed", datatype=BaseTypes.UINT32_T)
hvac_status_service.add_data_element(name="FanLeftSpeed", datatype=BaseTypes.UINT32_T)
hvac_status_service.add_operation(
    name="SetDegree",
    in_parameter={"Value": BaseTypes.UINT8_T},
)

my_interface = vafpy.ModuleInterface(name="DataExchangeInterface", namespace="demo")
my_interface.add_data_element(name="MyValue", datatype=BaseTypes.UINT32_T)
my_interface.add_operation(name="MyFunction", in_parameter={"MyValueIn": BaseTypes.UINT32_T}, out_parameter={"MyValueOut": BaseTypes.UINT32_T})
