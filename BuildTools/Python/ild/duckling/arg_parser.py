import argparse

#Definitions that effect the public behavior
PLATFORM_OPTIONS = ["android", "desktop"]
DEFAULT_PLATFORM = "desktop"
DEFAULT_TARGET = "ancona_game"
DO_NOT_BUILD_OPTION = "none"

BUILD_FLAG_HELP_TEXT = "\
        Build the ancona project for the given platform. If no platform is given then \
        the desktop version will be built.\
        "

RUN_FLAG_HELP_TEXT = "\
        Run a game in the Ancona project.  Specifying a target will execute \
        the corresponding cmake target.  If no target is given then {} will \
        run by default.\
        ".format(DEFAULT_TARGET)

DOC_FLAG_HELP = "Include if you want to generate documentation instead of building the game"

EPILOG_HELP_TEXT = \
        "Running duckling with no arguments will behave as if it was given the -b flag"

DESCRIPTION_HELP_TEXT = "Script used to automate the Ancona build process"


#Flags that are only used withing duckling_arg_parser.py
_RUN_FLAG_NOT_GIVEN = "do^not^run"
_BUILD_FLAG_NOT_GIVEN = "no^build^specified"

##
# @brief Parse arguments for duckling.
#
# @return A (ancona_platform, ancona_target) tuple.
#     ancona_platform := The platform the ancona engine should be built for.
#     ancona_target   := The target that should be run.
#
def parse():
    parser = create_parser()
    return create_tuple(parser.parse_args())


def create_parser():
    parser = argparse.ArgumentParser(description=DESCRIPTION_HELP_TEXT, epilog=EPILOG_HELP_TEXT)

    parser.add_argument(
            '-b', 
            dest="platform",
            nargs="?",
            const=DEFAULT_PLATFORM,
            choices = ["android", "desktop", DO_NOT_BUILD_OPTION],
            help=BUILD_FLAG_HELP_TEXT
            )

    parser.add_argument(
            '-r', 
            dest="target",
            nargs="?",
            const=_RUN_FLAG_NOT_GIVEN,
            metavar="target",
            help=RUN_FLAG_HELP_TEXT
            )

    parser.add_argument(
            '-docs',
            dest="generate_documentation",
            action="store_true",
            help=DOC_FLAG_HELP
            )
    
    return parser

def create_tuple(arguments):
    if not arguments.platform and not arguments.target:
        print("Ancona platform:",DEFAULT_TARGET,"Ancona Target:",None)
        return DEFAULT_TARGET,None,arguments.generate_documentation
    
    if arguments.platform in [None , DO_NOT_BUILD_OPTION]:
        ancona_platform = None
    elif arguments.platform == _BUILD_FLAG_NOT_GIVEN:
        ancona_platform = DEFAULT_PLATFORM
    else:
        ancona_platform = arguments.platform

    if arguments.target == _RUN_FLAG_NOT_GIVEN:
        ancona_target = DEFAULT_TARGET
    else:
        ancona_target = arguments.target

    print("Ancona platform:",ancona_platform,"Ancona Target:",ancona_target,"Generate documentation:",arguments.generate_documentation)
    return ancona_platform,ancona_target,arguments.generate_documentation

    
