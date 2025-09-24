# SageFrame: Blueprint and Game Mode Setup Guide

This guide explains how to use the C++ classes from the `SageFrame` plugin to create a playable level in Unreal Engine. You must complete the `INPUT_SETUP.md` guide before starting this one.

## 1. Create the Player Controller Blueprint

First, we'll create a Blueprint version of our player controller so we can assign our input assets to it.

1.  In the Content Browser, right-click and select `Blueprint Class`.
2.  In the "Pick Parent Class" window, expand the "All Classes" section and search for `ARTSPlayerController`. Select it and click `Create Blueprint`.
3.  Name the new Blueprint `BP_RTSPlayerController`.
4.  Open `BP_RTSPlayerController`. In the **Details** panel, find the `Input` category.
5.  Set the **RTS Mapping Context** property to your `IMC_RTS` asset.
6.  Assign each of your `IA_` assets (`IA_CameraPan`, `IA_Select`, etc.) to their corresponding properties.
7.  Compile and save the Blueprint.

## 2. Create a Unit Blueprint

Next, we need a pawn for the player controller to possess and move around.

1.  In the Content Browser, right-click and select `Blueprint Class`.
2.  Search for `AUnitBase` as the parent class and create the Blueprint.
3.  Name it `BP_RTSUnit`.
4.  Open `BP_RTSUnit`. In the **Components** panel, click `+ Add` and add a `Static Mesh Component`.
5.  In the **Details** panel for the Static Mesh Component, assign a simple mesh (e.g., `Shape_Cube` or `SM_ChamferCube`) so you can see the unit in the world.
6.  Compile and save the Blueprint.

## 3. Create and Configure the Game Mode

The Game Mode ties everything together, telling the level which classes to use for the player.

1.  In the Content Browser, create a new `Blueprint Class`.
2.  Select `GameModeBase` as the parent class.
3.  Name it `BP_RTSGameMode`.
4.  Open `BP_RTSGameMode`. In the **Details** panel, find the `Classes` section.
5.  Set **Player Controller Class** to `BP_RTSPlayerController`.
6.  Set **Default Pawn Class** to `BP_RTSUnit`.
7.  Compile and save the Blueprint.

## 4. Run the Level

You are now ready to test!

1.  Open the level you want to test in.
2.  Go to `Window` -> `World Settings`.
3.  In the **World Settings** panel, under the `Game Mode` section, set the **GameMode Override** to your `BP_RTSGameMode`.
4.  Place a `Player Start` actor in your level if you don't have one.
5.  Press **Play**.

You should now be able to fly the cube around using the WASD keys. When you press the input keys, you should also see the `UE_LOG` messages from the C++ code appearing in the **Output Log** (`Window` -> `Developer Tools` -> `Output Log`). This confirms that your C++ code, input assets, and Blueprints are all working together correctly.
