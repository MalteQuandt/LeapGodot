function(ReadConfigFile CONFIGFILEPATH)
    # Read the file given in the argument and set the variables as key value pairs, where the
    # keys are set as new variables in the parent scope.
    # param CONFIGFILEPATH: The file to read from
    file(STRINGS ${CONFIGFILEPATH} content)
    message(STATUS "Variables Read From Config File:")
    foreach(pair ${content})
        # strip leading space
        string(REGEX REPLACE "^[ ]+" "" pair ${pair})
        # Fetch name of the variable
        string(REGEX MATCH "^[^=]+" key ${pair})
        # Fetch the value of the variable
        string(REPLACE "${key}=" "" value ${pair})
        # Set the variable in the parent scope
        set(${key} "${value}" PARENT_SCOPE)
        message(STATUS "${key} = ${value}")
    endforeach()
endfunction()
