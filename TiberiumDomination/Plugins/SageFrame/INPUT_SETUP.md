# SageFrame: Enhanced Input Setup Guide

This guide details how to create the necessary Unreal Engine assets to make the C++ `ARTSPlayerController` functional. The Enhanced Input system requires two types of assets: **Input Actions** (what you are doing) and an **Input Mapping Context** (which key triggers what action).

Follow these steps in the Unreal Editor's Content Browser.

## 1. Create Input Action Assets

For each of the following, right-click in the Content Browser, go to `Input` -> `Input Action`, and give it the specified name.

| Asset Name      | Value Type      | Notes                                                                 |
|-----------------|-----------------|-----------------------------------------------------------------------|
| `IA_CameraPan`    | `Axis2D (Vector2D)` | Represents movement input for panning the camera (e.g., from WASD).     |
| `IA_CameraRotate` | `Axis1D (float)`  | Represents input for rotating the camera.                             |
| `IA_CameraZoom`   | `Axis1D (float)`  | Represents input for zooming the camera in and out (e.g., Mouse Wheel). |
| `IA_Select`       | `Digital (bool)`  | Represents the action of selecting a unit (e.g., Left Mouse Click).   |
| `IA_Command`      | `Digital (bool)`  | Represents the action of issuing a command (e.g., Right Mouse Click). |

## 2. Create the Input Mapping Context

Now, create the context that will hold all the key-to-action mappings.

1.  Right-click in the Content Browser, go to `Input` -> `Input Mapping Context`.
2.  Name the asset `IMC_RTS`.

## 3. Configure Mappings in `IMC_RTS`

Open the `IMC_RTS` asset. You will see a `Mappings` array. Click the `+` icon to add a new mapping for each of the actions you created.

### Camera Pan Mapping
- **Action:** `IA_CameraPan`
- **Key:** `W`
- **Modifiers:** `Swizzle Input Axis Values` (Order: YXZW)
- ---
- **Action:** `IA_CameraPan`
- **Key:** `S`
- **Modifiers:** `Swizzle Input Axis Values` (Order: YXZW), `Negate`
- ---
- **Action:** `IA_CameraPan`
- **Key:** `A`
- **Modifiers:** `Negate`
- ---
- **Action:** `IA_CameraPan`
- **Key:** `D`

### Camera Zoom Mapping
- **Action:** `IA_CameraZoom`
- **Key:** `Mouse Wheel Axis`

### Camera Rotate Mapping
- *This is often handled by holding a key like Middle Mouse Button and moving the mouse. For simplicity, we can initially map it to keys.*
- **Action:** `IA_CameraRotate`
- **Key:** `Q`
- **Modifiers:** `Negate`
- ---
- **Action:** `IA_CameraRotate`
- **Key:** `E`

### Select / Command Mappings
- **Action:** `IA_Select`
- **Key:** `Left Mouse Button`
- ---
- **Action:** `IA_Command`
- **Key:** `Right Mouse Button`

---

Once you have created these assets and configured the `IMC_RTS` mapping context, you can assign `IMC_RTS` to the `RTS Mapping Context` property on the `ARTSPlayerController` Blueprint (or its C++ defaults). This will make your input bindings live.
