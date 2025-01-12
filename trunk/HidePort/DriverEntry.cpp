#include "DriverEntry.h"
#include "Attach.h"
#include "MajorFunction.h"
#include "Cdo.h"
#include "GetInfo.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


_Function_class_(DRIVER_UNLOAD)
_IRQL_requires_(PASSIVE_LEVEL)
_IRQL_requires_same_
VOID Unload(_In_ struct _DRIVER_OBJECT * DriverObject)
{
    UNREFERENCED_PARAMETER(DriverObject);

    PAGED_CODE();

    DeleteControlDeviceObject();

    Detach(DriverObject);

    Sleep(3000);//等待一些挂起状态的IRP。注意：不是全部。
}


EXTERN_C DRIVER_INITIALIZE DriverEntry;
//#pragma INITCODE
//#pragma alloc_text(INIT, DriverEntry)
_Function_class_(DRIVER_INITIALIZE)
_IRQL_requires_same_
_IRQL_requires_(PASSIVE_LEVEL)
EXTERN_C NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath)
{
    NTSTATUS Status = STATUS_SUCCESS;

    UNREFERENCED_PARAMETER(RegistryPath);

    if (!KD_DEBUGGER_NOT_PRESENT) {
        KdBreakPoint();//__debugbreak();
    }

    PAGED_CODE();

    DriverObject->DriverUnload = Unload;

    for (int i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++) {
        DriverObject->MajorFunction[i] = GlobalMajorFunction;
    }

    //DriverObject->FastIoDispatch = &g_FastIoDispatch;

    Status = CreateControlDeviceObject(DriverObject);
    if (!NT_SUCCESS(Status)) {
        return Status;
    }

    EnumTcpTable();
    EnumUdpTable();

    Status = AttachDevice(DriverObject, L"\\Device\\Nsi", L"\\Device\\MyNsi", MY_NSI_DEVICE_TAG);

    EnumTcpTable();
    EnumUdpTable();

    return Status;
}
