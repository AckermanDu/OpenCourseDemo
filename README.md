# 腾讯公开课课程作业Demo
>基于UE5官方的FirstPerson模板实现的游戏Demo(C++实现)，因为网络问题仅上传了C++的源代码 :cry: :cry: :cry:

Demo运行视频链接：[游戏胜利演示](https://www.bilibili.com/video/BV1HaNxe1Eos/?spm_id_from=333.788.top_right_bar_window_history.content.click "点击访问") 
[游戏失败演示](https://www.bilibili.com/video/BV1waNxe1E4e/?spm_id_from=333.1007.top_right_bar_window_history.content.click "点击访问")

## 主要设计的C++类
### GameMode类
主要创建了游戏的胜利和失败逻辑，以及添加对应的胜利或失败UserWidget组件；添加了游戏的主界面UserWidget组件。
### Character类
玩家操控的角色C++类名为AGame2Character，角色的移动为模板初始移动，后续在蓝图类中调整了镜头的位置；为角色添加了最大生命值和当前生命中属性，其中最大生命值属性可以在蓝图中编辑；为角色订阅了碰撞委托，用于实现当角色被Projectile(子弹类)击中时，角色扣除20点生命值，并在屏幕上打印角色被集中的信息。
### EnemyCharacter类
作为敌人目标，该类继承自Character类，其控制方式由AIController控制；首先，该类区别于Character类的是实现了一个自动开火功能，用于攻击玩家，并且该类实现了一个健康组件并在EnemyCharacter的顶部显示其血条；其次，该类的控制AI使用了行为树，控制目标在一定范围内巡逻并且攻击敌人；最后，当敌人生命值小于等于0时，Destroy该对象。

## 学习心得
该Demo的制作学习，我对于UE5 C++的开发有了入门的认知，对于不同的功能应该在哪里实现都有了大致的把握，再也不是看到教程都得找半天的小白 :smile:。比如，初步了解了不同情况下应该使用哪种C++类、组件的使用方式以及意义、UPROPERTY和UFUNCTION这两类最常用的宏的使用、初步了解了委托了使用等等。最后，本Demo因为时间、设备等原因，只有最基本的游戏功能，主要是在这一过程中学到了很多UE5 C++的知识，以后有时间会完善该项目 :fist:。
