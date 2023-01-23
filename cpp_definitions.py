Import("env")

env.Append(CPPDEFINES=[
  ("BUILD_TYPE",  env.StringifyMacro(env.GetBuildType()))
])