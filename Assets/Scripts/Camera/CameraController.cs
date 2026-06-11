using UnityEngine;

public class CameraController : MonoBehaviour
{
    [Header("攝像機模式")]
    [SerializeField] private CameraMode cameraMode = CameraMode.FirstPerson;
    [SerializeField] private Transform trainCarBody;
    [SerializeField] private Vector3 firstPersonOffset = new Vector3(0, 1.6f, 0);
    [SerializeField] private Vector3 thirdPersonOffset = new Vector3(0, 2.5f, -3f);
    [SerializeField] private float lookSensitivity = 2f;
    
    private float rotationX = 0f;
    private float rotationY = 0f;

    private void Update()
    {
        HandleCameraInput();
        UpdateCameraPosition();
    }

    private void HandleCameraInput()
    {
        // 滑鼠控制視角
        if (Input.GetMouseButton(1)) // 右鍵
        {
            rotationX += Input.GetAxis("Mouse X") * lookSensitivity;
            rotationY -= Input.GetAxis("Mouse Y") * lookSensitivity;
            rotationY = Mathf.Clamp(rotationY, -90f, 90f);
        }

        // 攝像機模式切換
        if (Input.GetKeyDown(KeyCode.C))
        {
            SwitchCameraMode();
        }
    }

    private void UpdateCameraPosition()
    {
        if (trainCarBody == null) return;

        Vector3 targetOffset = cameraMode == CameraMode.FirstPerson ? firstPersonOffset : thirdPersonOffset;
        
        transform.position = trainCarBody.position + targetOffset;
        transform.rotation = Quaternion.Euler(rotationY, rotationX, 0);
    }

    private void SwitchCameraMode()
    {
        cameraMode = cameraMode == CameraMode.FirstPerson ? CameraMode.ThirdPerson : CameraMode.FirstPerson;
        Debug.Log($"切換到{(cameraMode == CameraMode.FirstPerson ? "第一人稱" : "第三人稱")}視角");
    }
}

public enum CameraMode
{
    FirstPerson,
    ThirdPerson,
    Exterior
}
