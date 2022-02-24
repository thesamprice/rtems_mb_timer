if { $argc != 1 } {
    puts stderr "Elf path required as input"
    exit 1
} else {
    set elf_path [lindex $argv 0]
}

connect

###############################################################################
# Use mb0 to access reset line for mb1 and pull mb1 out of reset
# xsdb load_cpu.tcl hello_world.elf 


###############################################################################
# TODO - Download from install directory once CMake changes are made
# Download elf to mb1
targets -set -nocase -filter {name =~ "microblaze*#0"  }
catch {stop}; after 1000
puts stderr "INFO: Downloading ELF file: $elf_path"

dow  $elf_path
con



