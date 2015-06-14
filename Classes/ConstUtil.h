#ifndef __CONSTUTIL_H__
#define __CONSTUTIL_H__

#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

//���ɳ���Ҫ�õ�����Դ
#define A_IMAGE       "da.png"
#define B_IMAGE       "fu.png"
#define C_IMAGE       "weng.png"


// �˵�����
#define MENU_LOGO     "menuLogo.png"
#define RAINBOW       "rainbow.png"
#define NORMAL_START  "normal_start.png"
#define PRESS_START   "press_start.png"
#define NORMAL_QUIT   "normal_quit.png"
#define PRESS_QUIT    "press_quit.png"
#define MUSIC_ON      "music_on.png"
#define MUSIC_OFF     "music_off.png"

#define MUSIC_KEY       "music_key"

//������
#define  DIALOG_BG "popuplayer/dialog_bg.png"
#define  BUTTON_BG1 "popuplayer/button_bg1.png"
#define  BUTTON_BG2 "popuplayer/button_bg2.png"
#define  BUTTON_BG3 "popuplayer/button_bg3.png"

//string_zh.plist�����ļ���Ӧ��keyֵ
#define OK  "ok"
#define CANCEL  "cancel"
#define DIALOG_TITLE    "dialog_title"
#define DIALOG_CONTENT  "dialog_content"
#define BUY_LAND_MSG  "buy_land_msg"

//�ؿ�ѡ��
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


//�ؿ�����
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


//��ɫ
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

#define MSG_GO "msg_go"                                 //button��Ϣ������Go��ť����/��
#define MSG_BUY "msg_buy_land"                          //������Ϣ
#define MSG_PICKONE_TOGO "msg_pickone_togo"             //����һ����ɫ�ߵ���Ϣ
#define MSG_PAY_TOLLS "msg_pay_tolls"                   //���ɹ�·�ѵ���Ϣ
#define MSG_AROUND_LAND "msg_around_land"               //�����ɫ��Χ�������¼�����Ϣ
#define MSG_RANDOM_ASK_EVENT "msg_random_ask_event"     //�ʺ�����¼�����Ϣ

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

//���ɹ�·�ѵļ���
const int MSG_PAY_TOLLS_1_TAG = 6;
const int MSG_PAY_TOLLS_2_TAG = 7;
const int MSG_PAY_TOLLS_3_TAG = 8;

const int MSG_AROUND_LAND_TAG = 9;
const int MSG_RANDOM_ASK_EVENT_TAG =10;

//���������ĵļ���
const int MSG_STRENGTH_UP30_TAG = 15;
const int MSG_STRENGTH_UP50_TAG = 16;
const int MSG_STRENGTH_UP80_TAG = 17;
const int MSG_MOVE_ONE_STEP_TAG = 19;
const int MSG_USE_SKILL_TAG = 23;
const int MSG_GAME_OVER_TAG = 24;


//�����������������Ҫ�Ľ�Ǯ
const int LAND_BLANK_MONEY = 1000;
const int LAND_LEVEL_1_MONEY = 2000;
const int LAND_LEVEL_2_MONEY = 3000;

//�������صľ���֡�ļ�
#define PLAYER1_1_PARTICLE_PLIST "images/showClick.plist"
#define PLAYER2_1_PARTICLE_PLIST "images/fire.plist"

#define PLAYER1_1_PARTICLE_PNG "images/foot1.png"
#define PLAYER2_1_PARTICLE_PNG "images/foot2.png"

#define PLAYER1_2_PARTICLE_PNG "images/starfish1.png"
#define PLAYER2_2_PARTICLE_PNG "images/starfish2.png"

#define PLAYER1_3_PARTICLE_PNG "images/heart1.png"
#define PLAYER2_3_PARTICLE_PNG "images/heart2.png"

const float TOAST_SHOW_TIME = 2.5f;

//�ʺ�����¼���Ӧ��ֵ
const int TAX_REBATES_TAG = 1;            //��������Ͷ�ʣ�����˰��10000
const int PAY_TAXES_TAG = 2;              //�����ϲ����񣬲���˰��20000
const int LOSS_STRENGTH_TAG =3;           //�ȵ��پƣ�������к�������Ĺ�
const int PHYSICAL_RECOVERY_TAG =4;       //���˴��裬�����ָ�
const int INVESTMENT_DIVIDENDS_TAG = 5 ;  //Ͷ�ʻ������ֺ�20000
const int INVESTMENT_LOSS_TAG = 6;        //Ͷ��ʧ�ܣ�����30000
 
//�ʺ��¼�������-------------��Ӧ���ĵ�keyֵ
#define  TAX_REBATES  "tax_rebates"
#define  PAY_TAXES "pay_taxes"
#define  LOSS_STRENGTH "loss_strength"
#define  PHYSICAL_RECOVERY "physical_recovery"
#define  INVESTMENT_DIVIDENDS "investment_dividends"
#define  INVESTMENT_LOSS "investment_loss"

//���ܶ�Ӧstring.plist�����ļ������keyֵ
#define RAIN "rain"                            
#define YOURS_IS_MINE  "yours_is_mine"
#define LOST_STRENGTH "lost_strength"
#define DOWN_GRADE "down_grade"
#define YOURS_IS_MINE_INFO "yours_is_mine_info"
#define YOUR_STRENGTH_IS_LOW "your_strength_is_low"
#define STRENGTH_UP "strength_up"


////******�������֡���Ч*******/////

#define BUTTON_CLICK "sound/click.wav"
#define BUTTON_CLICK_01 "sound/click_01.wav"
#define STORM_EFFECT "sound/storm.wav"
#define PARTICLE_EFFECT "sound/particle.mp3"

#define STORM_SPEAKING  "sound/storm_speaking.wav" //�������Ϯ �ݻٷ���һ��

#define BLOCK_THE_WAY "sound/effect_00056.wav" 
//

//����·������
#define P1_Speaking_00435  "sound/Speaking_00435.wav"//oh ����·��
#define P1_Speaking_00461  "sound/Speaking_00461.wav"//oh �ҵ�Ѫ��Ǯ
#define P1_Speaking_00475  "sound/Speaking_00475.wav"//�������� �����е���Ǯ
#define P1_Speaking_01060  "sound/Speaking_01060.wav"//�ϱ�����û��
#define P1_Speaking_01062  "sound/Speaking_01062.wav"//��ȥ�˲�������
//������˵ؿ�
#define P1_Speaking_00429  "sound/Speaking_00429.wav"//���Ұ�����Ϊ����
//���ݱ�����
#define P1_Speaking_00430  "sound/Speaking_00430.wav"//�ƽ�ض� �ø���
#define P1_Speaking_00464  "sound/Speaking_00464.wav"//̫����������
#define P1_Speaking_00469  "sound/Speaking_00469.wav"//��Ƥ������
#define P1_Speaking_00470  "sound/Speaking_00470.wav"//������̫��ͷ�϶���
#define P1_Speaking_00476  "sound/Speaking_00476.wav"//�����
//���ݱ��ݻ�
#define P1_Speaking_00462  "sound/Speaking_00462.wav"//�ô�ĵ���
#define P1_Speaking_00463  "sound/Speaking_00463.wav"//˭�Ҷ��ҵĵ�
#define P1_Speaking_00466  "sound/Speaking_00466.wav"//�����ƻ��ҵĺ���
#define P1_Speaking_00468  "sound/Speaking_00468.wav"//��Ļ���ɾ�
#define P1_Speaking_00474  "sound/Speaking_00474.wav"//����û�и��
#define P1_Speaking_01061  "sound/Speaking_01061.wav"//��û����
//�ݻٱ��˷���
#define P1_Speaking_00433  "sound/Speaking_00433.wav"//����л��
#define P1_Speaking_00437  "sound/Speaking_00437.wav"//ȫ����Ϊƽ��


//��ȡ��·��
#define P1_Speaking_00453  "sound/Speaking_00453.wav"//С����Ӫ �Ų���Ƿ
#define P1_Speaking_01059  "sound/Speaking_01059.wav"//ӬͷС��
#define P1_Speaking_01057  "sound/Speaking_01057.wav"//������Ӧ�õ�
//��������
#define P1_Speaking_01051  "sound/Speaking_01051.wav"//�𼵶���
#define P1_Speaking_01066  "sound/Speaking_01066.wav"//��������Լ�
//���
#define P1_Speaking_00458  "sound/Speaking_00458.wav"//��ʲô����
#define P1_Speaking_01067  "sound/Speaking_01067.wav"//���Ǹ������
//�Է�������˰
#define P1_Speaking_00452  "sound/Speaking_00452.wav"//����͵©˰


//����·������
#define P2_SPEAKING01 "sound/p2_Speaking01.wav" //Υ�½�����ôû�˹���
#define P2_QISIWOLE     "sound/p2_qisiwole.wav" //��������
#define P2_XINHAOKONGA  "sound/p2_xinhaokonga.wav" //���ĺ�ʹ��
#define P2_BUHUIBA  "sound/p2_buhuiba.wav" //�����
#define P2_PAYHIGH  "sound/p2_payhigh.wav" //����������·���շ�̫������
#define P2_QIANGQIANA  "sound/p2_qiangqiana.wav" //��Ǯ��
#define P2_HEBAOCHUXIE  "sound/p2_hebaochuxie.wav" //�ɰ����Ѫ
//������˵ؿ�
#define P2_BIEGUAIWO  "sound/p2_bieguaiwo.wav" //�����
#define P2_SPEAKING02 "sound/p2_Speaking02.wav" //�벻������һ�а�
#define P2_TIGER  "sound/p2_tiger.wav" // �ϻ������� ���ҵ���è
#define P2_NIDEJIUSHODE "sound/p2_nidejiushode.wav" //��ľ����ҵ� �ҵĻ����ҵ�
//���ݱ�����
#define P2_ZHENMIANMU  "sound/p2_zhenmianmu.wav" //���������������Ŀ��
#define P2_WODEDIQI  "sound/p2_wodediqi.wav" //˭͵���ҵĵ���
#define P2_HAOQIFU "sound/p2_haoqifu.wav" //����Ϊ������۸�
#define P2_WANGFA "sound/p2_wangfa.wav" // �⻹��������
//�ݻٱ��˷���
#define P2_NIGAIWOCHAI  "sound/p2_nigaiwochai.wav" //����ҾͲ�
#define P2_KANWODE "sound/p2_kanwode.wav" //���ҵ�
#define P2_HAIRENLE "sound/p2_hairenle.wav" //����Ҫ������
#define P2_BAOCHOU "sound/p2_baochou.wav" //�����ʱ����
//���ݱ��ݻ�
#define P2_WODEYANGFANG  "sound/p2_wodeyangfang.wav" //�ҵ���
#define P2_QIFURENJIA  "sound/p2_qifurenjia.wav" //�۸��˼�
#define P2_SHAQIANDAO  "sound/p2_shaqiandao.wav" //�����ɱǧ����
#define P2_LIANXIANGXIYU  "sound/p2_lianxiangxiyu.wav" //�㲻������ϧ��
#define P2_HAOJIUGAIHAO "p2_haojiugaihao.wav" //�˼һ��˺þòŸǺõ�

//��ȡ��·��
#define P2_RENBUWEIJI  "sound/p2_renbuweiji.wav" //�˲�Ϊ���������
#define P2_XIAOQI  "sound/p2_xiaoqi.wav" //С������
#define P2_RONGXING "sound/p2_rongxing.wav" //�������ǵ�����
#define P2_MANYI "sound/p2_manyi.wav" //�� �Һ�����
#define P2_XIAOFUPO "sound/p2_xiaofupo.wav" //����С����
#define P2_DUOGEI "sound/p2_duogei.wav" //��ô�����һ�㰡
//��������
#define P2_HIGHER       "sound/p2_higher.wav" //�ǵ�Խ��Խ��
#define P2_WANZHANGGAOLOU "sound/p2_wanzhanggaolou.wav" //���ɸ�¥ƽ����
//���
#define P2_BUYIT        "sound/p2_buyit.wav" //������
#define P2_HAODEKAISHI "sound/p2_haodekaishi.wav" //�õĿ�ʼ�ǳɹ���һ��
#define P2_RANGNIZHU "sound/p2_rangnizhu.wav" //�ҵ�Ư����������ס
#define P2_MAIWOBA  "sound/p2_maiwoba.wav" //�������Ұ�
//�Է�������˰
#define P2_TOUSHUI  "sound/p2_toushui.wav" //����һ��͵©˰������
#define P2_FALVZHICAI "sound/p2_falvzhicai.wav" //���ܷ��ɵ��Ʋð�
#define P2_GUOKU "sound/p2_guoku.wav" //��Ǯ�������
#define P2_NASHUI "sound/p2_nashui.wav" //��˰�ǹ���Ӧ��������


 

#define BG01_MP3 "sound/bg01.mp3" 
#define BG02_MP3 "sound/bg02.mp3" 
#define BG03_MP3 "sound/bg03.mp3" 

#define WALK_MP3 "sound/walk.mp3"


#endif