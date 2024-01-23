#!/bin/bash

# 设置测试的组
GROUP="root"

# 要测试的用户数组
USERS=("postfix")
# USERS=("postfix" "nscd" "chrony" "sshd" "dbus" "nobody" "ftp" "mail")
# 循环次数
LOOP_COUNT=1

echo "开始测试 gpasswd 命令效率..."

# 总时间统计
total_time=0

# 循环添加和删除用户
for (( i=1; i<=LOOP_COUNT; i++ ))
do
    echo "第 $i 次循环..."

    # 开始时间
    start_time=$(date +%s%3N)  # 获取当前时间（毫秒）

    # 添加用户到组
    for user in "${USERS[@]}"
    do
        ./gpasswd -a "$user" $GROUP
    done

    # 删除用户从组
    for user in "${USERS[@]}"
    do
        ./gpasswd -d "$user" $GROUP
    done

    # 结束时间
    end_time=$(date +%s%3N)  # 获取当前时间（毫秒）

    # 计算并累加这次循环的时间
    loop_time=$((end_time - start_time))
    total_time=$((total_time + loop_time))

    echo "第 $i 次循环耗时: $loop_time 毫秒"
done

echo "测试完成。总耗时: $total_time 毫秒"
