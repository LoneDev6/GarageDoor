raw_data = """
釣り針零号|[#Tool,#Needle]|0|0|#NotForSale|本|10
釣り針壱号|[#Tool,#Needle,#Gonbe]|0|0|1|本|10
釣り針弐号|[#Tool,#Needle,#Gonbe]|0|0|2|本|10
釣り針参号|[#Tool,#Needle,#Gonbe]|0|0|5|本|10
釣り針四号|[#Tool,#Needle,#Gonbe]|0|0|8|本|10
釣り針八号|[#Tool,#Needle,#Gonbe]|0|0|15|本|10
釣り針拾号|[#Tool,#Needle,#Gonbe]|0|0|30|本|10
釣り針百号|[#Tool,#Needle]|0|0|#NotForSale|本|#NotAvailable
釣り針百号改|[#Tool,#Needle]|0|0|#NotForSale|本|#NotAvailable
ツボガニ|[#Life,#Crab,#BaitA]|0|0|2|匹|#NotAvailable
タチバサミ|[#Life,#Crab,#BaitA,#Gonbe]|0|0|2|匹|10
サビネモドキ|[#Life,#Crab,#BaitA,#Gonbe]|0|0|4|匹|10
カエルダマシ|[#Life,#Crab,#BaitA,#Gonbe]|0|0|6|匹|10
オニガザミ|[#Life,#Crab,#BaitA]|0|0|100|匹|#NotAvailable
ゲドウ|[#Life,#Frog,#BaitA,#Gonbe]|0|0|20|匹|10
錆蛙|[#Life,#Frog,#BaitA]|0|0|40|匹|#NotAvailable
緑青錆蛙|[#Life,#Frog,#BaitA]|0|0|400|匹|#NotAvailable
キュウスイ（雄）|[#Life,#Frog,#BaitA]|0|0|680|匹|#NotAvailable
白子キュウスイ（雄）|[#Life,#Frog,#BaitA]|0|0|6800|匹|#NotAvailable
ヨウゲン|[#Life,#Frog,#BaitA]|0|0|10000|匹|#NotAvailable
朱ヨウゲン|[#Life,#Frog,#BaitA]|0|0|100000|匹|#NotAvailable
七色ヨウゲン|[#Life,#Frog,#BaitA]|0|0|400000|匹|#NotAvailable
角蛙|[#Life,#Frog,#BaitA]|0|0|160|匹|#NotAvailable
白子角蛙|[#Life,#Frog,#BaitA]|0|0|1600|匹|#NotAvailable
ネダマシ|[#Life,#Frog,#BaitA]|0|0|130|匹|#NotAvailable
白子ネダマシ|[#Life,#Frog,#BaitA]|0|0|1300|匹|#NotAvailable
一角|[#Life,#Frog,#BaitA]|0|0|440|匹|#NotAvailable
白子一角|[#Life,#Frog,#BaitA]|0|0|4400|匹|#NotAvailable
サシグチ|[#Life,#Frog,#BaitA]|0|0|200|匹|#NotAvailable
白子サシグチ|[#Life,#Frog,#BaitA]|0|0|2000|匹|#NotAvailable
ヘラグチ|[#Life,#Frog,#BaitA]|0|0|360|匹|#NotAvailable
白子ヘラグチ|[#Life,#Frog,#BaitA]|0|0|3600|匹|#NotAvailable
蟹喰い|[#Life,#Frog,#BaitA]|0|0|600|匹|#NotAvailable
白子蟹喰い|[#Life,#Frog,#BaitA]|0|0|6000|匹|#NotAvailable
筒耳|[#Life,#Frog,#BaitA]|0|0|480|匹|#NotAvailable
白子筒耳|[#Life,#Frog,#BaitA]|0|0|4800|匹|#NotAvailable
大一角|[#Life,#Frog,#BaitA]|0|0|1000|匹|#NotAvailable
黒子大一角|[#Life,#Frog,#BaitA]|0|0|10000|匹|#NotAvailable
モノモライ（雄）|[#Life,#Frog,#BaitA]|0|0|600|匹|#NotAvailable
白子モノモライ（雄）|[#Life,#Frog,#BaitA]|0|0|6000|匹|#NotAvailable
モノモライ（雌）|[#Life,#Frog,#BaitA]|0|0|3600|匹|#NotAvailable
白子モノモライ（雌）|[#Life,#Frog,#BaitA]|0|0|36000|匹|#NotAvailable
キュウスイ（雌）|[#Life,#Frog,#BaitA]|0|0|3000|匹|#NotAvailable
白子キュウスイ（雌）|[#Life,#Frog,#BaitA]|0|0|30000|匹|#NotAvailable
大蟹喰い|[#Life,#Frog,#BaitA]|0|0|2000|匹|#NotAvailable
白子大蟹喰い|[#Life,#Frog,#BaitA]|0|0|20000|匹|#NotAvailable
スイホウ|[#Life,#Frog,#BaitA]|0|0|20000|匹|#NotAvailable
白子スイホウ|[#Life,#Frog,#BaitA]|0|0|200000|匹|#NotAvailable
ワンスイ|[#Hidden,#System]|0|0|VOID|匹|#NotAvailable
なし|[#BaitB,#BaitC]|1|1|VOID|VOID|#NotAvailable
ゲドウ釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|50|VOID|1
錆蛙釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|50|VOID|1
角蛙釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
一角釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
大一角釣り情報|[#Info,#FishingInfo]|1|0|#NotForSale|VOID|#NotAvailable
ヘラグチ釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
蟹喰い釣り情報|[#Info,#FishingInfo]|1|0|#NotForSale|VOID|#NotAvailable
大蟹喰い釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|300|VOID|1
モノモライ（雄）釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
モノモライ（雌）釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
ネダマシ釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|50|VOID|1
キュウスイ（雄）釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|500|VOID|1
キュウスイ（雌）釣り情報|[#Info,#FishingInfo]|1|0|#NotForSale|VOID|1
サシグチ釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
筒耳釣り情報|[#Info,#FishingInfo,#Gonbe]|1|0|100|VOID|1
スイホウ釣り情報|[#Info,#FishingInfo]|1|0|#NotForSale|VOID|1
ヨウゲン釣り情報|[#Info,#FishingInfo]|1|0|#NotForSale|VOID|1
ワンスイ釣り情報|[#Info,#FishingInfo]|1|0|#NotForSale|VOID|1
順応液|[#Tool,#JunnouRecover,#BaitB,#Jirobe]|0|0|50|VOID|1
高級順応液|[#Tool,#JunnouRecover,#BaitB,#Jirobe]|0|0|100|VOID|1
特選順応液|[#Tool,#JunnouRecover,#BaitB,#Jirobe]|0|0|150|VOID|1
蟹味噌赤缶|[#Tool,#JunnouRecover,#BaitB,#Jirobe]|0|0|200|VOID|1
蟹味噌青缶|[#Tool,#JunnouRecover,#BaitB,#Jirobe]|0|0|800|VOID|1
フロッグオイル丸缶|[#Tool,#FuelCostDownTemporary,#BaitB,#Jirobe]|0|0|30|VOID|1
フロッグオイル角缶|[#Tool,#FuelCostDownTemporary,#BaitB,#Jirobe]|0|0|80|VOID|1
携帯用白瓦斯|[#Tool,#Refuel,#Jirobe]|0|0|30|VOID|1
撒き餌金印|[#Tool,#BaitB,#Gonbe,#BaitC]|0|0|20|VOID|1
撒き餌銀印|[#Tool,#BaitB,#Gonbe,#BaitC]|0|0|10|VOID|1
ビンドウ小|[#Tool,#Bindu,#Gonbe]|0|0|150|VOID|1
ビンドウ中|[#Tool,#Bindu,#Gonbe]|0|0|500|VOID|1
ビンドウ大|[#Tool,#Bindu]|0|0|#NotForSale|VOID|#NotAvailable
ビンドウ特大|[#Tool,#Bindu]|0|0|#NotForSale|VOID|#NotAvailable
銀皿|[#HomeItem,#Yoshibe]|1|0|500|VOID|1
送風機|[#HomeItem,#Yoshibe]|1|0|3000|VOID|1
送風機大|[#HomeItem,#Yoshibe]|1|0|15000|VOID|1
汚水煙管|[#HomeItem,#Yoshibe]|1|0|200000|VOID|1
照明器|[#HomeItem,#Yoshibe]|1|0|5000|VOID|1
リザーブタンク小|[#Other,#ReserveTank,#TropA]|1|0|500|VOID|1
リザーブタンク中|[#Other,#ReserveTank,#TropB]|1|0|1000|VOID|1
リザーブタンク大|[#Other,#ReserveTank,#TropC]|1|0|2000|VOID|1
リザーブタンク特大|[#Other,#ReserveTank]|1|0|#NotForSale|VOID|#NotAvailable
大口径気化器|[#Other,#Tune,#TropA,#Stage2]|1|0|700|VOID|1
集合管|[#Other,#Tune,#TropA,#Stage2]|1|0|800|VOID|1
強化バルブ|[#Other,#Tune,#TropA,#Stage3]|1|0|1200|VOID|1
過給機|[#Other,#Tune,#Stage3]|1|0|#NotForSale|VOID|#NotAvailable
強化フレーム|[#Other,#Tune,#Stage3]|1|0|#NotForSale|VOID|#NotAvailable
オイルクーラー|[#Other,#Tune,#TropA,#Stage4]|1|0|1000|VOID|1
ボアアップキット|[#Other,#Tune,#TropC,#Stage4]|1|0|3000|VOID|1
強化クランク|[#Other,#Tune,#TropC,#Stage4]|1|0|4000|VOID|1
４バルブヘッド|[#Other,#Tune,#TropD,#Stage0]|1|0|100000|VOID|1
ジェットセット|[#Other,#Tune,#Stage0]|1|0|#NotForSale|VOID|#NotAvailable
機械制御式燃料噴射装置|[#Other,#Tune,#TropD,#Stage0]|1|0|100000|VOID|1
チャンバー付集合管|[#Other,#Tune,#Stage0]|1|0|#NotForSale|VOID|#NotAvailable
台車壱式|[#Other,#FuelCostDown,#Honda]|1|0|500|VOID|1
台車弐式|[#Other,#FuelCostDown,#Honda]|1|0|2000|VOID|1
台車参式|[#Other,#FuelCostDown,#Honda]|1|0|5000|VOID|1
台車百式|[#Other,#FuelCostDown,#Honda]|1|0|100000|VOID|1
シェンの手紙|[#Info]|1|0|VOID|VOID|VOID
シェンのメモ１|[#Info]|1|0|VOID|VOID|VOID
シェンのメモ２|[#Info]|1|0|VOID|VOID|VOID
シェンのメモ３|[#Info]|1|0|VOID|VOID|VOID
シェンのメモ４|[#Info]|1|0|VOID|VOID|VOID
シェンのメモ５|[#Info]|1|0|VOID|VOID|VOID
壊れたオルゴール|[#Tool]|1|0|VOID|VOID|VOID
オルゴール|[#Tool]|1|0|VOID|VOID|VOID
釣り竿|[#Tool]|1|0|VOID|VOID|VOID
開かずの箱|[#Tool]|1|0|VOID|VOID|VOID
古い設計図|[#Info]|1|0|VOID|VOID|VOID
プシケの手紙|[#Info]|1|0|VOID|VOID|VOID
望遠鏡|[#Tool]|1|0|VOID|VOID|VOID
八号室の鍵|[#Tool]|1|0|VOID|VOID|VOID
ニトロ|[#Tool]|1|0|VOID|VOID|VOID
ジュースの夢日記|[#Info]|1|0|VOID|VOID|VOID
ルウの蝶ネジ|[#Tool]|1|0|VOID|VOID|VOID
原想体|[#Tool]|1|0|VOID|VOID|VOID
ダウジングコンパス|[#Tool]|1|0|VOID|VOID|VOID
白瓦斯屋年代記|[#Info]|1|0|VOID|VOID|VOID
開かずの箱の暗号|[#Info]|1|0|VOID|VOID|VOID
シェンの日記|[#Info]|1|0|VOID|VOID|VOID
汚水に関する研究報告|[#Info]|1|0|VOID|VOID|VOID
シャドーに関する考察|[#Info]|1|0|VOID|VOID|VOID
ヤンの夢日記|[#Info]|1|0|VOID|VOID|VOID
共鳴板|[#Tool]|1|0|VOID|VOID|VOID
メディチの部屋の鍵|[#Tool]|1|0|VOID|VOID|VOID
ラオの部屋の鍵|[#Tool]|1|0|VOID|VOID|VOID
給水塔の鍵|[#Tool]|1|0|VOID|VOID|VOID
銀幕の鍵|[#Tool]|1|0|VOID|VOID|VOID
再生石|[#Tool]|1|0|VOID|VOID|VOID
ステージ０パーツリスト|[#Info]|1|0|VOID|VOID|VOID
はじまりのスライド|[#Other,#Slide]|1|0|VOID|VOID|VOID
木馬のスライド|[#Other,#Slide]|1|0|VOID|VOID|VOID
ルウのスライド|[#Other,#Slide]|1|0|VOID|VOID|VOID
チェンのスライド|[#Other,#Slide]|1|0|VOID|VOID|VOID
シャドーマーダーショウ|[#Other,#Slide]|1|0|VOID|VOID|VOID
ヤンのスライド|[#Other,#Slide]|1|0|VOID|VOID|VOID
刻印石の洞窟へのスライド|[#Other,#Slide]|1|0|VOID|VOID|VOID
羊の歌の楽譜|[#Score]|1|0|VOID|VOID|VOID
ブルカニロの楽譜|[#Score]|1|0|VOID|VOID|VOID
ビスの楽譜|[#Score]|1|0|VOID|VOID|VOID
トーロップの楽譜|[#Score]|1|0|VOID|VOID|VOID
ガタリの楽譜|[#Score,#BaitB]|1|0|VOID|VOID|VOID
ルウの一番大切なもの|[#Score,#BaitB]|1|0|VOID|VOID|VOID
ノイズの楽譜|[#Score]|1|0|VOID|VOID|VOID
-- ポスター
フリークスショウ赤|[#Other,#Poster]|1|0|VOID|VOID|VOID
フリークスショウ青|[#Other,#Poster]|1|0|VOID|VOID|VOID
双頭機械青字|[#Other,#Poster]|1|0|VOID|VOID|VOID
双頭機械金字|[#Other,#Poster]|1|0|VOID|VOID|VOID
驚異の世界（道代・後期）|[#Other,#Poster]|1|0|VOID|VOID|VOID
驚異の世界（道代・前期）|[#Other,#Poster]|1|0|VOID|VOID|VOID
驚異の世界（レイコ・赤）|[#Other,#Poster]|1|0|VOID|VOID|VOID
驚異の世界（レイコ・紫）|[#Other,#Poster]|1|0|VOID|VOID|VOID
驚異の世界（シャン・赤）|[#Other,#Poster]|1|0|VOID|VOID|VOID
驚異の世界（シャン・紫）|[#Other,#Poster]|1|0|VOID|VOID|VOID
シャドーマーダーショウ赤|[#Other,#Poster]|1|0|VOID|VOID|VOID
シャドーマーダーショウ青|[#Other,#Poster]|1|0|VOID|VOID|VOID
反順応液ショウ後期|[#Other,#Poster]|1|0|VOID|VOID|VOID
反順応液ショウ前期|[#Other,#Poster]|1|0|VOID|VOID|VOID
フロッグオイルラベル赤|[#Other,#Poster]|1|0|VOID|VOID|VOID
フロッグオイルラベル黒|[#Other,#Poster]|1|0|VOID|VOID|VOID
蟹味噌ラベル赤|[#Other,#Poster]|1|0|VOID|VOID|VOID
蟹味噌ラベル青|[#Other,#Poster]|1|0|VOID|VOID|VOID
蟹味噌ラベル黄|[#Other,#Poster]|1|0|VOID|VOID|VOID
ファイヤーショウ金赤|[#Other,#Poster]|1|0|VOID|VOID|VOID
ファイヤーショウ緑|[#Other,#Poster]|1|0|VOID|VOID|VOID
ファイヤーショウ紫|[#Other,#Poster]|1|0|VOID|VOID|VOID
ハッピーアワー赤|[#Other,#Poster]|1|0|VOID|VOID|VOID
ハッピーアワー橙|[#Other,#Poster]|1|0|VOID|VOID|VOID
試し刷り１|[#Other,#Poster]|1|0|VOID|VOID|VOID
試し刷り２|[#Other,#Poster]|1|0|VOID|VOID|VOID
試し刷り３|[#Other,#Poster]|1|0|VOID|VOID|VOID
-- システム関係
白瓦斯屋スタンプ|[#system]|0|0|VOID|枚|VOID
船|[#System]|1|0|VOID|VOID|VOID
-- イベント関係
自室の白瓦斯屋スタンプ|[#Hidden,#system]|1|0|VOID|VOID|VOID
自室の釣り針壱号１０本|[#Hidden,#system]|1|0|VOID|VOID|VOID
自室のオルゴール|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の蟹味噌赤缶|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の双頭機械青字Ａ|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の双頭機械青字Ｂ|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の反順応液ショウ後期|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の試し刷り１Ａ|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の試し刷り１Ｂ|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の驚異の世界（シャン・赤）|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の釣り針四号|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔の釣り針弐号|[#Hidden,#system]|1|0|VOID|VOID|VOID
給水塔のビンドウ中|[#Hidden,#system]|1|0|VOID|VOID|VOID
八号室のビンドウ大|[#Hidden,#system]|1|0|VOID|VOID|VOID
ルウの部屋の釣り針３パック|[#Hidden,#system]|1|0|VOID|VOID|VOID
ルウの部屋のビンドウ大|[#Hidden,#system]|1|0|VOID|VOID|VOID
ルウの部屋のビンドウ中|[#Hidden,#system]|1|0|VOID|VOID|VOID
ヤンの隠し部屋の釣り針零号１０本|[#Hidden,#system]|1|0|VOID|VOID|VOID
ヤンの隠し部屋の釣り針百号１０本|[#Hidden,#system]|1|0|VOID|VOID|VOID
ヤンの隠し部屋の釣り針拾号１０本|[#Hidden,#system]|1|0|VOID|VOID|VOID
ヤンの隠し部屋の原想体|[#Hidden,#system]|1|0|VOID|VOID|VOID
弐号店裏口の白瓦斯屋スタンプ１００００枚|[#Hidden,#system]|1|0|VOID|VOID|VOID
本田工場の白瓦斯屋スタンプ１０００枚|[#Hidden,#system]|1|0|VOID|VOID|VOID
灯台１Ｆビンドウ大|[#Hidden,#system]|1|0|VOID|VOID|VOID
灯台１Ｆビンドウ特大|[#Hidden,#system]|1|0|VOID|VOID|VOID
灯台１Ｆ試し刷りＡ|[#Hidden,#system]|1|0|VOID|VOID|VOID
灯台１Ｆ試し刷りＢ|[#Hidden,#system]|1|0|VOID|VOID|VOID

"""

# Dictionary translations NAME -> English
NAME_TRANSLATIONS = {
    "釣り針零号": "Fish Hook No. 0",
    "釣り針壱号": "Fish Hook No. 1",
    "釣り針弐号": "Fish Hook No. 2",
    "釣り針参号": "Fish Hook No. 3",
    "釣り針四号": "Fish Hook No. 4",
    "釣り針八号": "Fish Hook No. 8",
    "釣り針拾号": "Fish Hook No. 10",
    "釣り針百号": "Fish Hook No. 100",
    "釣り針百号改": "Fish Hook No. 100+",

    "ツボガニ": "Pot Crab",
    "タチバサミ": "Tachibasami Crab",  # guessed
    "サビネモドキ": "Rust Mimic Crab",  # guessed
    "カエルダマシ": "Frog Impostor",  # guessed
    "オニガザミ": "Oni Crab",  # guessed

    "ゲドウ": "Outsider Frog",  # guessed
    "錆蛙": "Rust Frog",  # guessed
    "緑青錆蛙": "Verdigris Rust Frog",  # guessed

    "キュウスイ（雄）": "Male Kyusui",  # guessed (base name from your text)
    "白子キュウスイ（雄）": "Albino Male Kyusui",  # guessed
    "ヨウゲン": "Dancing Eye",
    "朱ヨウゲン": "Crimson Dancing Eye",  # guessed
    "七色ヨウゲン": "Seven-Color Dancing Eye",  # guessed

    "角蛙": "Horned Frog",  # guessed
    "白子角蛙": "Albino Horned Frog",  # guessed
    "ネダマシ": "Decoy Frog",  # guessed
    "白子ネダマシ": "Albino Decoy Frog",  # guessed
    "一角": "Unihorn",  # guessed (from Big Unihorn in your text)
    "白子一角": "Albino Unihorn",  # guessed
    "サシグチ": "Stabber-Mouth Frog",  # guessed
    "白子サシグチ": "Albino Stabber-Mouth Frog",  # guessed
    "ヘラグチ": "Heraguchi Frog",  # guessed
    "白子ヘラグチ": "Albino Heraguchi Frog",  # guessed
    "蟹喰い": "Crab Eater",
    "白子蟹喰い": "Albino Crab Eater",  # guessed
    "筒耳": "Tube-Ear Frog",  # guessed
    "白子筒耳": "Albino Tube-Ear Frog",  # guessed
    "大一角": "Big Unihorn",
    "黒子大一角": "Dark Big Unihorn",  # guessed

    "モノモライ（雄）": "Male Monomorai",  # guessed
    "白子モノモライ（雄）": "Albino Male Monomorai",  # guessed
    "モノモライ（雌）": "Female Monomorai",  # guessed
    "白子モノモライ（雌）": "Albino Female Monomorai",  # guessed
    "キュウスイ（雌）": "Female Kyusui",
    "白子キュウスイ（雌）": "Albino Female Kyusui",  # guessed
    "大蟹喰い": "Big Crab Eater",  # guessed
    "白子大蟹喰い": "Albino Big Crab Eater",  # guessed
    "スイホウ": "Suihou",
    "白子スイホウ": "Albino Suihou",  # guessed
    "ワンスイ": "Wansui",
    "なし": "Nothing",  # guessed (literally “none”)

    "ゲドウ釣り情報": "Outsider Frog Fishing Info",  # guessed
    "錆蛙釣り情報": "Rust Frog Fishing Info",  # guessed
    "角蛙釣り情報": "Horned Frog Fishing Info",  # guessed
    "一角釣り情報": "Unihorn Fishing Info",  # guessed
    "大一角釣り情報": "Big Unihorn Fishing Info",
    "ヘラグチ釣り情報": "Heraguchi Frog Fishing Info",  # guessed
    "蟹喰い釣り情報": "Crab Eater Fishing Info",
    "大蟹喰い釣り情報": "Big Crab Eater Fishing Info",  # guessed
    "モノモライ（雄）釣り情報": "Male Monomorai Fishing Info",  # guessed
    "モノモライ（雌）釣り情報": "Female Monomorai Fishing Info",  # guessed
    "ネダマシ釣り情報": "Decoy Frog Fishing Info",  # guessed
    "キュウスイ（雄）釣り情報": "Male Kyusui Fishing Info",  # guessed
    "キュウスイ（雌）釣り情報": "Female Kyusui Fishing Info",
    "サシグチ釣り情報": "Stabber-Mouth Frog Fishing Info",  # guessed
    "筒耳釣り情報": "Tube-Ear Frog Fishing Info",  # guessed
    "スイホウ釣り情報": "Suihou Fishing Info",
    "ヨウゲン釣り情報": "Dancing Eye Fishing Info",
    "ワンスイ釣り情報": "Wansui Fishing Info",

    "順応液": "Identity Fluid",  # guessed
    "高級順応液": "High-Grade Identity Fluid",  # guessed
    "特選順応液": "Special Identity Fluid",
    "蟹味噌赤缶": "Red Can of Crab Miso",
    "蟹味噌青缶": "Blue Can of Crab Miso",
    "フロッグオイル丸缶": "Round Can of Flog Oil",  # guessed (kept your “Flog Oil” typo)
    "フロッグオイル角缶": "Square Can of Flog Oil",  # guessed
    "携帯用白瓦斯": "Portable White Gas",  # guessed
    "撒き餌金印": "Gold Mark Scatter Bait",
    "撒き餌銀印": "Silver Mark Scatter Bait",

    "ビンドウ小": "Small Trap",
    "ビンドウ中": "Medium Trap",
    "ビンドウ大": "Large Trap",
    "ビンドウ特大": "Extra Large Trap",

    "銀皿": "Silver Plate",  # guessed
    "送風機": "Fan",  # guessed
    "送風機大": "Large Fan",  # guessed
    "汚水煙管": "Sewage Pipe",  # guessed
    "照明器": "Lamp",  # guessed

    "リザーブタンク小": "Small Reserve Tank",  # guessed
    "リザーブタンク中": "Medium Reserve Tank",
    "リザーブタンク大": "Large Reserve Tank",  # guessed
    "リザーブタンク特大": "Extra Large Reserve Tank",

    "大口径気化器": "Large-Bore Carburetor",  # guessed
    "集合管": "Assembly Tube",  # guessed
    "強化バルブ": "Reinforced Valves",  # guessed
    "過給機": "Supercharger",  # guessed
    "強化フレーム": "Reinforced Frame",  # guessed
    "オイルクーラー": "Oil Cooler",  # guessed
    "ボアアップキット": "Bore-Up Kit",  # guessed
    "強化クランク": "Reinforced Crank",  # guessed
    "４バルブヘッド": "4-Valve Head",  # guessed
    "ジェットセット": "Jet Set",
    "機械制御式燃料噴射装置": "Mechanical Fuel Injection System",  # guessed
    "チャンバー付集合管": "Chambered Assembly Tube",

    "台車壱式": "Cart Model I",  # guessed
    "台車弐式": "Cart Model II",  # guessed
    "台車参式": "Cart Model III",  # guessed
    "台車百式": "Cart Model 100",  # guessed

    "シェンの手紙": "Shen's Letter",
    "シェンのメモ１": "Shen's Note 1",  # guessed
    "シェンのメモ２": "Shen's Note 2",  # guessed
    "シェンのメモ３": "Shen's Note 3",  # guessed
    "シェンのメモ４": "Shen's Note 4",  # guessed
    "シェンのメモ５": "Shen's Note 5",  # guessed

    "壊れたオルゴール": "Broken Music Box",
    "オルゴール": "Music Box",
    "釣り竿": "Fishing Rod",
    "開かずの箱": "Locked Box",  # guessed
    "古い設計図": "Old Blueprints",
    "プシケの手紙": "Psyche's Letter",
    "望遠鏡": "Telescope",
    "八号室の鍵": "Room 8 Key",
    "ニトロ": "Nitro",
    "ジュースの夢日記": "Juice's Dream Diary",  # guessed
    "ルウの蝶ネジ": "Ru's Thumbscrew",
    "原想体": "Protothought",
    "ダウジングコンパス": "Dowsing Compass",
    "白瓦斯屋年代記": "The White Gas House Chronicles",
    "開かずの箱の暗号": "Locked Box Code",
    "シェンの日記": "Shen's Dream Diary",
    "汚水に関する研究報告": "Research Report on Sewage",
    "シャドーに関する考察": "Reflections on the Shadow",
    "ヤンの夢日記": "Yan's Dream Diary",
    "共鳴板": "Resonance Board",  # guessed

    "メディチの部屋の鍵": "Medici's Room Key",
    "ラオの部屋の鍵": "Rao's Room Key",
    "給水塔の鍵": "Water Tower Key",
    "銀幕の鍵": "Silver Screen Key",
    "再生石": "Reviving Stone",
    "ステージ０パーツリスト": "Stage 0 Parts List",

    "はじまりのスライド": "Intro Slide",
    "木馬のスライド": "Wooden Horse Slide",
    "ルウのスライド": "Ru's Slide",
    "チェンのスライド": "Chen's Slide",
    "シャドーマーダーショウ": "Shadow Murder Show",
    "ヤンのスライド": "Yan's Slide",
    "刻印石の洞窟へのスライド": "Ending Slide",

    "羊の歌の楽譜": "Lament of the Lamb",
    "ブルカニロの楽譜": "Vulcaniro's Score",
    "ビスの楽譜": "Vis' Score",
    "トーロップの楽譜": "Torlop's Score",
    "ガタリの楽譜": "Gatari's Score",
    "ルウの一番大切なもの": "Ru's Treasure",
    "ノイズの楽譜": "Noise Score",

    # Posters
    "フリークスショウ赤": "Freakshow Red",
    "フリークスショウ青": "Freakshow Blue",
    "双頭機械青字": "Two-Headed Machine Blue",
    "双頭機械金字": "Two-Headed Machine Gold",
    "驚異の世界（道代・後期）": "World of Wonders＠(Michiyo - Latter Period)",  # guessed
    "驚異の世界（道代・前期）": "World of Wonders＠(Michiyo - First Semester)",
    "驚異の世界（レイコ・赤）": "World of Wonders Red (Reiko)",
    "驚異の世界（レイコ・紫）": "World of Wonders Purple (Reiko)",
    "驚異の世界（シャン・赤）": "World of Wonders Red (Shan)",
    "驚異の世界（シャン・紫）": "World of Wonders Purple (Shan)",
    "シャドーマーダーショウ赤": "Shadow Murder Show Red",
    "シャドーマーダーショウ青": "Shadow Murder Show Blue",
    "反順応液ショウ後期": "Late Anti-Identity Fluid Show",
    "反順応液ショウ前期": "Early Anti-Identity Fluid Show",
    "フロッグオイルラベル赤": "Flog Oil Red",
    "フロッグオイルラベル黒": "Flog Oil Label Black",
    "蟹味噌ラベル赤": "Crab Miso Label Red",
    "蟹味噌ラベル青": "Crab Miso Label Blue",
    "蟹味噌ラベル黄": "Crab Miso Label Yellow",
    "ファイヤーショウ金赤": "Fire Show Gold and Red",
    "ファイヤーショウ緑": "Fire Show Green",
    "ファイヤーショウ紫": "Fire Show Purple",
    "ハッピーアワー赤": "Happy Hour Red",
    "ハッピーアワー橙": "Happy Hour Orange",
    "試し刷り１": "Test Print 1",  # guessed
    "試し刷り２": "Test Print 2",  # guessed
    "試し刷り３": "Test Print 3",  # guessed

    # System
    "白瓦斯屋スタンプ": "White Gas House Stamps",
    "船": "Ship",  # guessed

    # Event-related items (internal)
    "自室の白瓦斯屋スタンプ": "Bedroom White Gas House Stamps",  # guessed
    "自室の釣り針壱号１０本": "Bedroom Fish Hooks No. 1 x10",  # guessed
    "自室のオルゴール": "Bedroom Music Box",  # guessed

    "給水塔の蟹味噌赤缶": "Water Tower Red＠Can of Crab Miso",  # guessed
    "給水塔の双頭機械青字Ａ": "Water Tower Two-Headed＠Machine Blue A",  # guessed
    "給水塔の双頭機械青字Ｂ": "Water Tower Two-Headed＠Machine Blue B",  # guessed
    "給水塔の反順応液ショウ後期": "Water Tower Late＠Anti-Identity Fluid Show",  # guessed
    "給水塔の試し刷り１Ａ": "Water Tower Test Print 1A",  # guessed
    "給水塔の試し刷り１Ｂ": "Water Tower Test Print 1B",  # guessed
    "給水塔の驚異の世界（シャン・赤）": "Water Tower World＠of Wonders Red (Shan)",  # guessed
    "給水塔の釣り針四号": "Water Tower Fish Hook No. 4",  # guessed
    "給水塔の釣り針弐号": "Water Tower Fish Hook No. 2",  # guessed
    "給水塔のビンドウ中": "Water Tower Medium Trap",  # guessed

    "八号室のビンドウ大": "Room 8 Large Trap",  # guessed
    "ルウの部屋の釣り針３パック": "Ru's Room 3 Packs of Fish Hooks",  # guessed
    "ルウの部屋のビンドウ大": "Ru's Room Large Trap",  # guessed
    "ルウの部屋のビンドウ中": "Ru's Room Medium Trap",  # guessed

    "ヤンの隠し部屋の釣り針零号１０本": "Yan's Hidden Room＠Fish Hooks No. 0 x10",  # guessed
    "ヤンの隠し部屋の釣り針百号１０本": "Yan's Hidden Room＠Fish Hooks No. 100 x10",  # guessed
    "ヤンの隠し部屋の釣り針拾号１０本": "Yan's Hidden Room＠Fish Hooks No. 10 x10",  # guessed
    "ヤンの隠し部屋の原想体": "Yan's Hidden Room Protothought",  # guessed

    "弐号店裏口の白瓦斯屋スタンプ１００００枚": "Back Door of Shop No. 2＠White Gas House Stamps x10000",  # guessed
    "本田工場の白瓦斯屋スタンプ１０００枚": "Honda Factory White＠Gas House Stamps x1000",  # guessed

    "灯台１Ｆビンドウ大": "Lighthouse 1F Large Trap",  # guessed
    "灯台１Ｆビンドウ特大": "Lighthouse 1F Extra Large Trap",  # guessed
    "灯台１Ｆ試し刷りＡ": "Lighthouse 1F Test Print A",  # guessed
    "灯台１Ｆ試し刷りＢ": "Lighthouse 1F Test Print B",  # guessed
}


UNIT_TRANSLATIONS = {
    "本": "total were obtained.",
    "匹": "total were obtained.",
    "枚": "total were obtained.",
    "匹": "total were obtained.",
    "VOID": "was obtained.",
    "": "was obtained.",
}

def parse_raw(raw):
  unit_partials = {}
  name_partials = {}

  for line in raw.splitlines():
    line = line.strip()
    if not line or line.startswith("--"):
      continue

    parts = line.split("|")
    if len(parts) < 6:
      continue

    name = parts[0]
    unit = parts[5]

    # 1) Traduzione nome item
    if name in NAME_TRANSLATIONS:
      name_partials[name] = NAME_TRANSLATIONS[name]
    else:
      name_partials[name] = "<MISSING>"

    # 2) Traduzione unità (crea pattern come "本を手に入れた")
    if unit in UNIT_TRANSLATIONS:
      key = f"{unit}を手に入れた"
      unit_partials[key] = UNIT_TRANSLATIONS[unit]

  # 3) Always add base fallback
  unit_partials["を手に入れた"] = "was obtained."

  # Merge units first, then names
  partials = {}
  for key in sorted(unit_partials.keys()):
    partials[key] = unit_partials[key]
  for key in sorted(name_partials.keys()):
    partials[key] = name_partials[key]

  return partials

def export_partials(partials):
    print("[Partials]")
    for key in partials.keys():
        print(f"{key}={partials[key]}")


if __name__ == "__main__":
    partials = parse_raw(raw_data)
    export_partials(partials)
