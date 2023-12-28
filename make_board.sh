echo -e "[\033[0;31mSTART\033[0m]"
./build.sh arm64

USER_NAME="9930343-Z100"
SOURCE_PATH="/share/$USER_NAME/"
SOURCE_NAME="ui-home.zip"

if [ "$1" != "" ]; then
    SOURCE_PATH+="$1"
    echo -e "[\033[1;34mLogging\033[0m]: $SOURCE_PATH"
    if [ -d $SOURCE_PATH ]; then # When folder already created
        # concatenating string
        REMOVE_SOURCE="$SOURCE_PATH/$SOURCE_NAME"

        if [ -e $REMOVE_SOURCE ]; then # Checking whether this file is exist
            # Remove old source
            rm $REMOVE_SOURCE
            echo -e "[\033[1;34mLogging\033[0m]: Removed $SOURCE_NAME from $REMOVE_SOURCE"
        else
            exit 1
        fi
    else
        echo -e "[\033[1;36mCommand\033[0m]: mkdir $SOURCE_PATH"
        mkdir "$SOURCE_PATH"
    fi
    SOURCE_PATH+="/"
    cp -f "$SOURCE_NAME" "$SOURCE_PATH"    
    echo -e "[\033[1;36mCommand\033[0m]: cp $SOURCE_NAME to $SOURCE_PATH"
else
    # concatenating string
    REMOVE_SOURCE="$SOURCE_PATH$SOURCE_NAME"
    if [ -f "$REMOVE_SOURCE" ]; then # Checking whether this file is exist
        rm -rf "$REMOVE_SOURCE"
        echo -e "[\033[1;34mLogging\033[0m]: Removed $SOURCE_NAME from $REMOVE_SOURCE"
    else
        exit 1
    fi
    cp -f "$SOURCE_NAME" "$SOURCE_PATH"
    echo -e "[\033[1;36mCommand\033[0m]: Copied new $SOURCE_NAME to $SOURCE_PATH"
fi

echo -e "[\033[1;32mCOMPLETED\033[0m]"