#include "GameScene.hpp"

gh::GameScene::GameScene(std::unique_ptr<Network>&& network) 
	: Scene(), network_(std::move(network)), 
	bg_layer_(std::make_unique<BackgroundLayer>()), 
	hex_layer_(std::make_unique<HexagonFrameLayer>()) ,
	player_(std::make_unique<Player>("TestPlayer1")),
	field_layer_(std::make_unique<FieldLayer>(this->segments_))
{}

gh::GameScene::~GameScene() {}

void gh::GameScene::prepareLayer(LayerManager * layer_manager) {
	this->bg_layer_->initialize();
	this->hex_layer_->initialize();

	std::shared_ptr<sf::Font> font = std::make_shared<sf::Font>();
	font->loadFromFile("media/RictyDiminished-Regular.ttf");

	this->player_->initialize(font, 0);

	this->field_layer_->initialize();

	//レイヤーの追加
	layer_manager->addLayer(this->bg_layer_, 0);
	layer_manager->addLayer(this->hex_layer_, 0);
	layer_manager->addLayer(this->player_, 0);
	layer_manager->addLayer(this->field_layer_, 0);

	//テスト
	//this->segments_.push_back(Segment(Segment::kTriangleSmall, SegmentPos(4, 5), SegmentPos(4, 5), SegmentPos(6, 7), 0));
	//this->segments_.push_back(Segment(Segment::kTrapezoidSmall, SegmentPos(4, 6), SegmentPos(4, 5), SegmentPos(4, 6), 1));
	this->segments_.push_back(Segment(Segment::kTrapezoidBig, SegmentPos(2, 6), SegmentPos(6, 10), SegmentPos(10, 12), 0));
	this->segments_.push_back(Segment(Segment::kTrapezoidBig, SegmentPos(2, 6), SegmentPos(6, 10), SegmentPos(10, 12), 0));
	//this->segments_.push_back(Segment(Segment::kDiamondSmall, SegmentPos(4, 6), SegmentPos(5, 6), SegmentPos(6, 7), 1));
	//this->segments_.push_back(Segment(Segment::kDiamondBig, SegmentPos(5, 9), SegmentPos(5, 8), SegmentPos(4, 6), 0));
	//this->segments_.push_back(Segment(Segment::kTrapezoidSmall, SegmentPos(4, 6), SegmentPos(4, 5), SegmentPos(4, 6), 1));
	//this->segments_.push_back(Segment(Segment::kTrapezoidSmall, SegmentPos(4, 6), SegmentPos(4, 5), SegmentPos(4, 6), 1));

}

int gh::GameScene::update(void) {



	return 0;
}
