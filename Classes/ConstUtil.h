#ifndef __CONSTUTIL_H__
#define __CONSTUTIL_H__

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

//过渡场景要用到的资源
#define A_IMAGE       "da.png"
#define B_IMAGE       "fu.png"
#define C_IMAGE       "weng.png"


// 菜单场景
#define MENU_LOGO     "menuLogo.png"
#define RAINBOW       "rainbow.png"
#define NORMAL_START  "normal_start.png"
#define PRESS_START   "press_start.png"
#define NORMAL_QUIT   "normal_quit.png"
#define PRESS_QUIT    "press_quit.png"
#define MUSIC_ON      "music_on.png"
#define MUSIC_OFF     "music_off.png"

#define MUSIC_KEY       "music_key"

//弹出框
#define  DIALOG_BG "popuplayer/dialog_bg.png"
#define  BUTTON_BG1 "popuplayer/button_bg1.png"
#define  BUTTON_BG2 "popuplayer/button_bg2.png"
#define  BUTTON_BG3 "popuplayer/button_bg3.png"

//string_zh.plist中文文件对应的key值
#define OK  "ok"
#define CANCEL  "cancel"
#define DIALOG_TITLE    "dialog_title"
#define DIALOG_CONTENT  "dialog_content"
#define BUY_LAND_MSG  "buy_land_msg"

//关卡选择
#define BACK_NORMAL  "images/back_normal.png"
#define BACK_SELECTED  "images/back_pressed.png"

#define BEACH_ITEM   "map/beach_item.png"
#define SEA_ITEM     "map/sea_item.png"
#define SNOW_ITEM    "map/snow_item.png"

#define STAGE_BACKGROUND  "map/stage_background2.png"

#define BUTTON_NORMAL   "images/LS01.png"
#define BUTTON_SELECTED   "images/LS02.png"
#define BUTTON_DISABLE   "images/LS03.png"

#define BUTTON_ENTER_NORMAL     "images/LS07.png"
#define BUTTON_ENTER_SELECTED   "images/LS08.png"


//关卡基类
#define RIGHT_BANNER      "map/right_banner.png"
#define PLAYER_ME         "map/player1.png"
#define PLAYER_ENEMY1     "map/player2.png"
#define GO_BUTTON_NORMAL  "map/go_normal.png"
#define GO_BUTTON_SELECTED "map/go_press.png"

#define PATH_MARK_1 "map/mark1.png"
#define PATH_MARK_2 "map/mark2.png"
#define PATH_MARK_3 "map/mark3.png"
#define PATH_MARK_4 "map/mark4.png"
#define PATH_MARK_5 "map/mark5.png"
#define PATH_MARK_6 "map/mark6.png"


//角色
#define PLAYER_ME_ANIM "map/player1_anim.png"
#define PLAYER_ENEMY1_ANIM "map/player2_anim.png"
#define PLAYER1_ANIM_PLIST   "map/player1_anim.plist"
#define PLAYER1_ANIM_PNG "map/player1_anim.png"

#define PLAYER2_ANIM_PLIST "map/player2_anim.plist"
#define PLAYER2_ANIM_PNG "map/player2_anim.png"

#define PLAYER_1_NAME "player1"
const int PLAYER_1_TAG = 1;
#define PLAYER_2_NAME "player2"
const int PLAYER_2_TAG = 2;

const int tiledWidth = 32;
const int tiledHeight = 32;

#define MSG_GO "msg_go"                                 //button消息，控制Go按钮的隐/现
#define MSG_BUY "msg_buy_land"                          //购买消息
#define MSG_PICKONE_TOGO "msg_pickone_togo"             //让下一个角色走的消息
#define MSG_PAY_TOLLS "msg_pay_tolls"                   //缴纳过路费的消息
#define MSG_AROUND_LAND "msg_around_land"               //处理角色周围的土地事件的消息
#define MSG_RANDOM_ASK_EVENT "msg_random_ask_event"     //问号随机事件的消息

#define MSG_STRENGTH_UP "msg_strength_up"

#define MSG_MOVE_ONE_STEP "msg_move_one_step"

#define MSG_USE_SKILL "msg_use_skill"
#define MSG_GAME_OVER "msg_game_over"

const int MSG_GO_HIDE_TAG = 0;
const int MSG_GO_SHOW_TAG = 1;

const int MSG_BUY_BLANK_TAG  = 2;
const int MSG_BUY_LAND_1_TAG = 3;
const int MSG_BUY_LAND_2_TAG = 4;

const int MSG_PICKONE_TOGO_TAG =5;

//缴纳过路费的级别
const int MSG_PAY_TOLLS_1_TAG = 6;
const int MSG_PAY_TOLLS_2_TAG = 7;
const int MSG_PAY_TOLLS_3_TAG = 8;

const int MSG_AROUND_LAND_TAG = 9;
const int MSG_RANDOM_ASK_EVENT_TAG =10;

//增加体力的的级别
const int MSG_STRENGTH_UP30_TAG = 15;
const int MSG_STRENGTH_UP50_TAG = 16;
const int MSG_STRENGTH_UP80_TAG = 17;
const int MSG_MOVE_ONE_STEP_TAG = 19;
const int MSG_USE_SKILL_TAG = 23;
const int MSG_GAME_OVER_TAG = 24;


//购买或升级土地所需要的金钱
const int LAND_BLANK_MONEY = 1000;
const int LAND_LEVEL_1_MONEY = 2000;
const int LAND_LEVEL_2_MONEY = 3000;

//购买土地的精灵帧文件
#define PLAYER1_1_PARTICLE_PLIST "images/showClick.plist"
#define PLAYER2_1_PARTICLE_PLIST "images/fire.plist"

#define PLAYER1_1_PARTICLE_PNG "images/foot1.png"
#define PLAYER2_1_PARTICLE_PNG "images/foot2.png"

#define PLAYER1_2_PARTICLE_PNG "images/starfish1.png"
#define PLAYER2_2_PARTICLE_PNG "images/starfish2.png"

#define PLAYER1_3_PARTICLE_PNG "images/heart1.png"
#define PLAYER2_3_PARTICLE_PNG "images/heart2.png"

const float TOAST_SHOW_TIME = 2.5f;

//问号随机事件对应的值
const int TAX_REBATES_TAG = 1;            //政府鼓励投资，返还税金10000
const int PAY_TAXES_TAG = 2;              //政府严查账务，补交税金20000
const int LOSS_STRENGTH_TAG =3;           //喝到假酒，上吐下泻，体力耗光
const int PHYSICAL_RECOVERY_TAG =4;       //吃了大补丸，体力恢复
const int INVESTMENT_DIVIDENDS_TAG = 5 ;  //投资获利，分红20000
const int INVESTMENT_LOSS_TAG = 6;        //投资失败，亏损30000
 
//问号事件的描述-------------对应中文的key值
#define  TAX_REBATES  "tax_rebates"
#define  PAY_TAXES "pay_taxes"
#define  LOSS_STRENGTH "loss_strength"
#define  PHYSICAL_RECOVERY "physical_recovery"
#define  INVESTMENT_DIVIDENDS "investment_dividends"
#define  INVESTMENT_LOSS "investment_loss"

//技能对应string.plist语言文件里面的key值
#define RAIN "rain"                            
#define YOURS_IS_MINE  "yours_is_mine"
#define LOST_STRENGTH "lost_strength"
#define DOWN_GRADE "down_grade"
#define YOURS_IS_MINE_INFO "yours_is_mine_info"
#define YOUR_STRENGTH_IS_LOW "your_strength_is_low"
#define STRENGTH_UP "strength_up"


////******背景音乐、音效*******/////

#define BUTTON_CLICK "sound/click.wav"
#define BUTTON_CLICK_01 "sound/click_01.wav"
#define STORM_EFFECT "sound/storm.wav"
#define PARTICLE_EFFECT "sound/particle.mp3"

#define STORM_SPEAKING  "sound/storm_speaking.wav" //龙卷风侵袭 摧毁房屋一栋

#define BLOCK_THE_WAY "sound/effect_00056.wav" 
//

//交过路费声音
#define P1_Speaking_00435  "sound/Speaking_00435.wav"//oh 哈利路亚
#define P1_Speaking_00461  "sound/Speaking_00461.wav"//oh 我的血汗钱
#define P1_Speaking_00475  "sound/Speaking_00475.wav"//算了算了 老子有的是钱
#define P1_Speaking_01060  "sound/Speaking_01060.wav"//老本都快没了
#define P1_Speaking_01062  "sound/Speaking_01062.wav"//拿去了不用找了
//抢夺别人地块
#define P1_Speaking_00429  "sound/Speaking_00429.wav"//让我把他据为己有
//房屋被抢夺
#define P1_Speaking_00430  "sound/Speaking_00430.wav"//黄金地段 让给你
#define P1_Speaking_00464  "sound/Speaking_00464.wav"//太不给面子了
#define P1_Speaking_00469  "sound/Speaking_00469.wav"//你皮子痒啊
#define P1_Speaking_00470  "sound/Speaking_00470.wav"//竟敢在太岁头上动土
#define P1_Speaking_00476  "sound/Speaking_00476.wav"//算你狠
//房屋被摧毁
#define P1_Speaking_00462  "sound/Speaking_00462.wav"//好大的胆子
#define P1_Speaking_00463  "sound/Speaking_00463.wav"//谁敢动我的地
#define P1_Speaking_00466  "sound/Speaking_00466.wav"//竟敢破坏我的好事
#define P1_Speaking_00468  "sound/Speaking_00468.wav"//拆的还真干净
#define P1_Speaking_00474  "sound/Speaking_00474.wav"//你有没有搞错啊
#define P1_Speaking_01061  "sound/Speaking_01061.wav"//真没良心
//摧毁别人房屋
#define P1_Speaking_00433  "sound/Speaking_00433.wav"//不必谢我
#define P1_Speaking_00437  "sound/Speaking_00437.wav"//全部夷为平地


//收取过路费
#define P1_Speaking_00453  "sound/Speaking_00453.wav"//小本经营 概不赊欠
#define P1_Speaking_01059  "sound/Speaking_01059.wav"//蝇头小利
#define P1_Speaking_01057  "sound/Speaking_01057.wav"//这是我应得的
//升级房子
#define P1_Speaking_01051  "sound/Speaking_01051.wav"//别嫉妒我
#define P1_Speaking_01066  "sound/Speaking_01066.wav"//我真佩服自己
//买地
#define P1_Speaking_00458  "sound/Speaking_00458.wav"//盖什么好呢
#define P1_Speaking_01067  "sound/Speaking_01067.wav"//我是个大地主
//对方被罚收税
#define P1_Speaking_00452  "sound/Speaking_00452.wav"//别想偷漏税


//交过路费声音
#define P2_SPEAKING01 "sound/p2_Speaking01.wav" //违章建筑怎么没人管哪
#define P2_QISIWOLE     "sound/p2_qisiwole.wav" //气死我了
#define P2_XINHAOKONGA  "sound/p2_xinhaokonga.wav" //我心好痛啊
#define P2_BUHUIBA  "sound/p2_buhuiba.wav" //不会吧
#define P2_PAYHIGH  "sound/p2_payhigh.wav" //不觉得这条路的收费太贵了吗
#define P2_QIANGQIANA  "sound/p2_qiangqiana.wav" //抢钱啊
#define P2_HEBAOCHUXIE  "sound/p2_hebaochuxie.wav" //荷包大出血
//抢夺别人地块
#define P2_BIEGUAIWO  "sound/p2_bieguaiwo.wav" //别怪我
#define P2_SPEAKING02 "sound/p2_Speaking02.wav" //想不到有这一招吧
#define P2_TIGER  "sound/p2_tiger.wav" // 老虎不发威 把我当病猫
#define P2_NIDEJIUSHODE "sound/p2_nidejiushode.wav" //你的就是我的 我的还是我的
//房屋被抢夺
#define P2_ZHENMIANMU  "sound/p2_zhenmianmu.wav" //终于认清你的真面目了
#define P2_WODEDIQI  "sound/p2_wodediqi.wav" //谁偷了我的地契
#define P2_HAOQIFU "sound/p2_haoqifu.wav" //别以为老娘好欺负
#define P2_WANGFA "sound/p2_wangfa.wav" // 这还有王法吗
//摧毁别人房屋
#define P2_NIGAIWOCHAI  "sound/p2_nigaiwochai.wav" //你盖我就拆
#define P2_KANWODE "sound/p2_kanwode.wav" //看我的
#define P2_HAIRENLE "sound/p2_hairenle.wav" //我又要害人了
#define P2_BAOCHOU "sound/p2_baochou.wav" //报仇的时候到了
//房屋被摧毁
#define P2_WODEYANGFANG  "sound/p2_wodeyangfang.wav" //我的洋房
#define P2_QIFURENJIA  "sound/p2_qifurenjia.wav" //欺负人家
#define P2_SHAQIANDAO  "sound/p2_shaqiandao.wav" //你这个杀千刀的
#define P2_LIANXIANGXIYU  "sound/p2_lianxiangxiyu.wav" //你不会怜香惜玉啊
#define P2_HAOJIUGAIHAO "p2_haojiugaihao.wav" //人家花了好久才盖好的

//收取过路费
#define P2_RENBUWEIJI  "sound/p2_renbuweiji.wav" //人不为己天诛地灭
#define P2_XIAOQI  "sound/p2_xiaoqi.wav" //小气吧啦
#define P2_RONGXING "sound/p2_rongxing.wav" //这是你们的荣幸
#define P2_MANYI "sound/p2_manyi.wav" //恩 我很满意
#define P2_XIAOFUPO "sound/p2_xiaofupo.wav" //我是小富婆
#define P2_DUOGEI "sound/p2_duogei.wav" //怎么不多给一点啊
//升级房子
#define P2_HIGHER       "sound/p2_higher.wav" //盖的越高越好
#define P2_WANZHANGGAOLOU "sound/p2_wanzhanggaolou.wav" //万丈高楼平地起
//买地
#define P2_BUYIT        "sound/p2_buyit.wav" //买了它
#define P2_HAODEKAISHI "sound/p2_haodekaishi.wav" //好的开始是成功的一半
#define P2_RANGNIZHU "sound/p2_rangnizhu.wav" //我的漂亮房子让你住
#define P2_MAIWOBA  "sound/p2_maiwoba.wav" //这块地卖我吧
//对方被罚收税
#define P2_TOUSHUI  "sound/p2_toushui.wav" //看你一副偷漏税的样子
#define P2_FALVZHICAI "sound/p2_falvzhicai.wav" //接受法律的制裁吧
#define P2_GUOKU "sound/p2_guoku.wav" //交钱给国库吧
#define P2_NASHUI "sound/p2_nashui.wav" //纳税是国民应尽的义务


 

#define BG01_MP3 "sound/bg01.mp3" 
#define BG02_MP3 "sound/bg02.mp3" 
#define BG03_MP3 "sound/bg03.mp3" 

#define WALK_MP3 "sound/walk.mp3"


#endif