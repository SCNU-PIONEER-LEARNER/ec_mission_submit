## git介绍

*Git
是一个开源的分布式版本控制系统，用于敏捷高效地处理任何或小或大的项目。如果你无法理解，你可以将它看成把文件保存在云端的搬运工，帮你把文件搬到云端服务器
eg：GitHub，coding，gitlab*

## 安装git
网上搜索git并下载
> ***首先查看系统是否已经安装好git了***\
> git\
> ***若返回error等报错，翻译一下，如果没有安装git，接着下一步***\
<img width="1373" height="744" alt="image" src="https://github.com/user-attachments/assets/5d9de8ad-ae41-40b6-9500-fe9ec7263d42" />

## git配置
>  git config \--global user.name \"aaa\"
>  ***\"aaa"中的内容为你的英文名，随便***\
>  git config \--global user.email \"aa@qq.com\" ***换成你的邮箱***\

## 使用git
使用git clone可以直接把仓库中所有文件都克隆下来
>  ***账号为注册GitHub的邮箱，密码是GitHub的密码***
> git clone -b branch_name 代码仓库中的ssh链接 , -b是克隆指定分支到本地\
<img width="1693" height="291" alt="87f46765497ba817c6cc3ec338a220f8" src="https://github.com/user-attachments/assets/7c745436-9c67-4495-a52a-ea3dc38c0871" />

> 也可以直接git clone ,然后git checkout -b branch_name\
> <img width="1493" height="446" alt="0f8b03a871dd984f274a19ef8f0920c6" src="https://github.com/user-attachments/assets/2355236e-7a45-4416-8a5b-00dd53cb1615" />

你的本地仓库由 git 维护的三棵"树"组成。第一个是你的
工作目录，它持有实际文件；第二个是
暂存区（Index），它像个缓存区域，临时保存你的改动；最后是
HEAD，它指向你最后一次提交的结果。

现在将文件传上云端分三步

> 1、添加到暂存区
>
> 2、对上传行为进行备注
>
> 3、送上云端

>***提交任务文件夹***\
>git add .\
>
>***提交说明***\
>git commit -m \"\<commit\>\"\
>
>***类型前缀：***\
>***feat: - 新功能/算法实现***\
>***fix: - bug修复***\
>***docs: - 文档更新***\
>***refactor: - 代码重构***\
>
>***假如我完成了任务1.1***\
>git commit -m \"feat: Finish task1.1\"\
>git push origin branch_name\
>

