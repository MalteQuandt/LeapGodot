# Check if a string starts with another string
#
# param string The string to check
# param string_to_check The string to check for
#
# return if the string starts with the search string
function(string_starts_with str string_to_check)
    string(FIND "${str}" "${string_to_check}" output)
    # ugly but whatever
    if("${output}" EQUAL 0)
        set(STRING_STARTS_WITH_OUTPUT true PARENT_SCOPE)
    else()
        set(STRING_STARTS_WITH_OUTPUT false PARENT_SCOPE)
    endif()
endfunction()

function(ReadConfigFile CONFIGFILEPATH)
    # Read the file given in the argument and set the variables as key value pairs, where the
    # keys are set as new variables in the parent scope.
    # param CONFIGFILEPATH: The file to read from
    file(STRINGS ${CONFIGFILEPATH} content)
    foreach(pair ${content})
        string_starts_with(${pair} "#")
        if(STRING_STARTS_WITH_OUTPUT)
            # skip comment lines
            continue()
        endif()
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

