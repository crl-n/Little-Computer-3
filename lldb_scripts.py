import lldb

def __lldb_init_module(debugger, internal_dict):
    debugger.HandleCommand("type summary add -F lldb_scripts.vm_summary t_vm")
    pass

reg_names = [
    'R_R0',
    'R_R1',
    'R_R2',
    'R_R3',
    'R_R4',
    'R_R5',
    'R_R6',
    'R_R7',
    'R_PC',
    'R_COND',
    'R_COUNT'
]
def vm_summary(valobj, internal_dict, options):
    summary_string = "{\n"
    memory, regs, running, *other = valobj.get_value_child_list()
    summary_string += "  " + str(memory) + "\n"
    summary_string += "  " + str(running) + "\n"
    summary_string += "  (" + regs.GetTypeName() + ") regs = {\n"
    for i, reg in enumerate(regs):
        summary_string += "    {}: {},\n".format(reg_names[i], reg.GetValue())
    summary_string += "  }\n}"
    return summary_string
