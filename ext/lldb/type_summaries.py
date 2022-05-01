import lldb


def __lldb_init_module(debugger, dict):
    print("Loaded extension for smollisp")
    debugger.HandleCommand(
        'type summary add -F type_summaries.ValueSummary smollisp_Value')


def ValueSummary(value: lldb.SBValue, _):
    kind: lldb.SBValue = value.GetChildMemberWithName("kind")
    kind: str = kind.GetValue()
    if kind == "SMOLLISP_VALUE_KIND_INT32":
        int32: lldb.SBValue = value.GetChildMemberWithName("int32")
        int32 = int32.GetValueAsSigned()
        return f"(int32 {int32})"
    elif kind == "SMOLLISP_VALUE_KIND_NONE":
        return "(none)"
    elif kind == "SMOLLISP_VALUE_KIND_STRING":
        string: lldb.SBValue = value.GetChildMemberWithName(
            "string").GetChildMemberWithName("buf")
        string = string.GetSummary()
        return f"(string {string})"
    else:
        return "(<invalid>)"
