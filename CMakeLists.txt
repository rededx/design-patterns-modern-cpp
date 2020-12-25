cmake_minimum_required(VERSION 3.5)

project(CppDesignPatterns)

set(PATTERNS
    abstractFactory
    factoryMethod
    builder
    prototype
    singleton
    
    adapter
    bridge
    composite
    decorator
    facade
    flyweight
    proxy
    
    chainOfResponsibility
    command
    iterator
    mediator
    memento
    observer
    # interpreter
    # state
    # strategy
    # template-method
    # visitor
)

find_package(Threads REQUIRED)

foreach(_dir IN ITEMS ${PATTERNS})
    file(GLOB _files "${_dir}/*.cpp")
    message(STATUS "Pattern `${_dir}':")

    foreach(_file IN ITEMS ${_files})

        get_filename_component(_file_name
                                ${_file} NAME
        )

        set(_project_name "${_file_name}")
        message(STATUS "  ${_dir}/${_file_name} is going to be built")
        
        add_executable(${_project_name} "${_dir}/${_file_name}")
       
        set_property(TARGET ${_project_name} PROPERTY CXX_STANDARD 17)
        target_link_libraries(${_project_name} Threads::Threads)
    endforeach()
    
endforeach()
