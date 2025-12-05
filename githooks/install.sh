#!/usr/bin/env bash

# 创建文件夹
function create_directory() {
    local directory=${1}
    if [ ! -e ${directory} ]; then
        mkdir -p ${directory}
    fi
}

# 递归拷贝
function recursive_copy() {
    local source_dir=${1}
    local target_dir=${2}

    if [ -d ${source_dir} ]; then
        create_directory ${target_dir}

        for file in $(ls ${source_dir}); do
            recursive_copy ${source_dir}/${file} ${target_dir}/${file}
        done
    elif [ -f ${source_dir} ]; then
        cp -p -f ${source_dir} ${target_dir}
        echo "cover file: ${target_dir}"
    fi
}

function main() {
    local source_dir="./hooks"
    local target_dir="../.git/hooks"

    recursive_copy "${source_dir}" "${target_dir}"
}

main "$@"
