//
//  titleLabelLayer.h
//  CutCutCut
//
//  Created by 光 渡邊 on 12/07/08.
//  Copyright __MyCompanyName__ 2012年. All rights reserved.
//
#define calculate_determinant_2x2(x1,y1,x2,y2) x1*y2-y1*x2
#define calculate_determinant_2x3(x1,y1,x2,y2,x3,y3) x1*y2+x2*y3+x3*y1-y1*x2-y2*x3-y3*x1
#define frandom (float)arc4random()/UINT64_C(0x100000000)
#define frandom_range(low,high) ((high-low)*frandom)+low
#define random_range(low,high) (arc4random()%(high-low+1))+low
#define midpoint(a,b) (float)(a+b)/2

typedef enum _Tag
{
    kTagNabeTop = 1
} Tag;

enum {
	kTagParentNode = 100,
	kTagNabe,
	kTagNabebuta,
	kTagNabeFront,
	kTagButton
};

#import <GameKit/GameKit.h>

// When you import this file, you import all the cocos2d classes
#import "cocos2d.h"
#import "Box2D.h"
#import "GLES-Render.h"

#import "PolygonSprite.h"
#import "RayCastCallback.h"

#import "ContactListener.h"

//Pixel to metres ratio. Box2D uses metres as the unit for measurement.
//This ratio defines how many pixels correspond to 1 Box2D "metre"
//Box2D is optimized for objects of 1x1 metre therefore it makes sense
//to define the ratio so that your most common object type is 1x1 metre.
#define PTM_RATIO 32
#define NABE_SPEED 2
#define MIN_CUT_AREA 1.0
// zOrderの管理はどうするべき?
#define Z_NABE_FRONT 100
#define Z_NABE 20
#define Z_NABEBUTA 110
#define Z_BUTTON 15
#define Z_SHIBUKI 90
#define Z_VEGE 50
#define Z_VEGE_SLICED 50
#define Z_BG_BLACK 100

// GameLayer
@interface GameLayer : CCLayer <GKAchievementViewControllerDelegate, GKLeaderboardViewControllerDelegate>
{
	b2World* world;					// strong ref
    b2Body* groundBody;
	GLESDebugDraw *m_debugDraw;		// strong ref
    
    
    CGPoint _startPoint;
    CGPoint _endPoint;
    
    RayCastCallback *_rayCastCallback;
    
    b2MouseJoint *_mouseJoint;
    
    // 野菜を画面外からpushするための変数
    double _nextPushTime;
    double _pushInterval;
    int _tmPushCount;
    
    // ナベを画面下からズズッとするための変数
    BOOL _isNabeMoving;
    
    // オブジェクトのcutのon/offを設定
    BOOL _canSliceObject;
    
    // タッチを呈しする
    BOOL _canTouch;
    
    // どの野菜を作成するかを決めるために利用する配列
    NSMutableArray *_vegeArray;
    
    NSTimer *_createVegeTimer;
    ContactListener* _contactListener;
    // ナベに入った内容を保存しておくやつ
    NSMutableDictionary *_nabeContents;
    
}

// returns a CCScene that contains the GameLayer as the only child
+(CCScene *) scene;

@property(nonatomic,readwrite)NSMutableDictionary *nabeContents;


-(b2Vec2*)arrangeVertices:(b2Vec2*)vertices count:(int)count;
-(void)splitPolygonSprite:(PolygonSprite*)sprite;
-(BOOL)areVerticesAcceptable:(b2Vec2*)vertices count:(int)count;
-(b2Body*)createBodyWithPosition:(b2Vec2)position rotation:(float)rotation vertices:(b2Vec2*)vertices vertexCount:(int32)count density:(float)density friction:(float)friction restitution:(float)restitution;
-(void)destroyMouseJoint:(b2Body*)body;
-(BOOL)hasMouseJoint:(b2Body*)body;

@end

