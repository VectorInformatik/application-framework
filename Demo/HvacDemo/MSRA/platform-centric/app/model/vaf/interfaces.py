from vaf import BaseTypes, vafpy

from .msra import *

my_interface = vafpy.ModuleInterface(name="DataExchangeInterface", namespace="demo")
my_interface.add_data_element(name="MyValue", datatype=BaseTypes.UINT32_T)
my_interface.add_operation(name="MyFunction", in_parameter={"MyValueIn": BaseTypes.UINT32_T}, out_parameter={"MyValueOut": BaseTypes.UINT32_T})
