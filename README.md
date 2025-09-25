# CSES

This repository contains my solutions to the [CSES](https://cses.fi/) problems.

## Setting up Debugging

To set up debugging, create a folder `.vscode`. In this folder, create two files:

- `launch.json`
- `tasks.json`

In `launch.json`, add a configuration for `gdb (Launch)`. Then, change the program
to be `${fileDirname}/${fileBasenameNoExtension}.out`

Next, in `tasks.json`, add the following text:

```json
{
  "tasks": [
    {
      "label": "build",
      "command": "g++",
      "args": [
        "-g",
        "${file}",
        "-o",
        "${fileDirname}/${fileBasenameNoExtension}.out"
      ],
      "type": "cppbuild"
    }
  ]
}
```

Finally, go back to `launch.json` and set the `preLaunchTask` for our launch configuration
to be `build`
