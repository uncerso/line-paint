/*
  ==============================================================================

    Toolbar.cpp
    Created: 28 Oct 2017 9:38:07pm
    Author:  uncerso

  ==============================================================================
*/

#include "LineSettings.h"
#include "LineComponent.h"
#include "CentralComponent.h"

LineSettings::LineSettings()
	: Component("LineSettings")
	, defaultSettings(true, nullptr, 10, LineComponent::LineType::rounded, Colours::cornflowerblue)
{
	laf.setColourScheme(LookAndFeel_V4::getMidnightColourScheme());
	setLookAndFeel(&laf);

	addAndMakeVisible(colourButton);
	colourButton.addActionListener(this);
	colourButton.selectColour(defaultSettings.getColour());

	addAndMakeVisible(lineThickness);
	lineThickness.setTextValueSuffix(" px");
	lineThickness.addListener(this);
	lineThickness.addActionListener(this);
	lineThickness.setRange(1, 100, 1);
	lineThickness.setValue(3);
	addAndMakeVisible(lineThicknessLabel);
	lineThicknessLabel.setText("Line thickness: ", NotificationType::dontSendNotification);
	lineThicknessLabel.attachToComponent(&lineThickness, false);

	roundedType.setClickingTogglesState(true);
	roundedType.setButtonText("Rounded");
	roundedType.addListener(this);
	addAndMakeVisible(roundedType);

	boundBoxType.setClickingTogglesState(true);
	boundBoxType.setButtonText("Bound box");
	boundBoxType.addListener(this);
	addAndMakeVisible(boundBoxType);

	deleteLine.setButtonText("Delete this line");
	deleteLine.addListener(this);
	addAndMakeVisible(deleteLine);

	for (int i = 0; i < 2; ++i) {
		TextButton *b = dashedTypeButtons.add(new TextButton());
		addAndMakeVisible(b);
		b->setRadioGroupId(42);
		b->setClickingTogglesState(true);
		b->addListener(this);
		switch (i) {
		case 0:
			b->setConnectedEdges(Button::ConnectedOnRight);
			b->setButtonText("Solid");
			break;
		case 1:
			b->setConnectedEdges(Button::ConnectedOnLeft);
			b->setButtonText("Dashed");
			break;
		default:    break;
		}
	}
	dashedTypeButtons.getUnchecked(0)->setToggleState(true, NotificationType::dontSendNotification);

	for (int i = 0; i < 2; ++i) {
		CustomSlider *s = dashedSettings.add(new CustomSlider());
		addAndMakeVisible(s);
		s->setTextValueSuffix(" px");
		s->addListener(this);
		s->addActionListener(this);
		s->setRange(1, 100, 1);
		s->setValue(8);
	}

	addAndMakeVisible(gpType);
	gpType.setText("Line types\n\n");
	addAndMakeVisible(gpDashedSettings);
	gpDashedSettings.setText("Dashed settings\n\n");
}

LineSettings::~LineSettings() {
	setLookAndFeel(nullptr);
	//deleteAllChildren();
}

void LineSettings::paint(Graphics &canvas) {
	canvas.fillAll(laf.getCurrentColourScheme().getUIColour(juce::LookAndFeel_V4::ColourScheme::UIColour::windowBackground));
}

void LineSettings::resized() {
	//double sk = getDesktopScaleFactor();
	int sliderLeft = proportionOfWidth(0.1f);
	int width = proportionOfWidth(0.8f);
	laf.setFontSize(proportionOfHeight(0.02f));

	lineThickness.setBounds(sliderLeft, proportionOfHeight(0.05f), width, proportionOfHeight(0.05f));
	lineThickness.setTextBoxStyle(Slider::TextBoxLeft, false, (int)(lineThickness.getWidth() * 0.3), lineThickness.getTextBoxHeight());

	gpType.setBounds(sliderLeft >> 1, proportionOfHeight(0.15f), (getWidth() + width ) >> 1, proportionOfHeight(0.25f));
	gpDashedSettings.setBounds(sliderLeft >> 1, proportionOfHeight(0.45f), (getWidth() + width ) >> 1, proportionOfHeight(0.2f));

	for (int i = 0; i < dashedTypeButtons.size(); ++i)
		dashedTypeButtons.getUnchecked(i)->setBounds(sliderLeft + i * (width >> 1), proportionOfHeight(0.2f), (width >> 1), proportionOfHeight(0.05f));

	for (int i = 0; i < dashedSettings.size(); ++i)
		dashedSettings.getUnchecked(i)->setBounds(sliderLeft, proportionOfHeight(0.5f) + i * proportionOfHeight(0.05f), width, proportionOfHeight(0.05f));

	roundedType.setBounds(sliderLeft,  proportionOfHeight(0.3f), (width >> 1), proportionOfHeight(0.05f));
	boundBoxType.setBounds(sliderLeft + (width >> 1),  proportionOfHeight(0.3f), (width >> 1), proportionOfHeight(0.05f));

	colourButton.setBounds(sliderLeft,  proportionOfHeight(0.7f), width, proportionOfHeight(0.05f));

	deleteLine.setBounds(sliderLeft,  proportionOfHeight(0.8f), width, proportionOfHeight(0.05f));

}

void LineSettings::actionListenerCallback(const String &s) {
	//jassert(s.size() == 1);
	switch (s[0]) {
	case 'H': // change colourButton
		if (LineComponent::selected)
			LineComponent::selected->setColour(colourButton.findColour(TextButton::buttonColourId));
		else
			defaultSettings.colour = colourButton.findColour(TextButton::buttonColourId);
		break;
	case 'C': // create colourSelector
		startChange();
		break;
	case 'R': // remove colourSelector
		endChange();
		break;
	case 'D': // mouse down on the slider
		startChange();
		break;
	case 'U': // mouse up on the slider
		endChange();
		break;
	default: break;
	}
}

void LineSettings::sliderValueChanged(Slider *slider) {
	if (slider == &lineThickness) {
		if (LineComponent::selected)
			LineComponent::selected->setLineThickness(lineThickness.getValue());
		else
			defaultSettings.lineThickness = lineThickness.getValue();
		return;
	}
	if (slider == dashedSettings.getUnchecked(0)) {
		if (LineComponent::selected)
			LineComponent::selected->setDashedValue1((unsigned int)slider->getValue());
		else
			defaultSettings.dashedValue1 = (unsigned int)slider->getValue();
		return;
	}
	if (slider == dashedSettings.getUnchecked(1)) {
		if (LineComponent::selected)
			LineComponent::selected->setDashedValue2((unsigned int)slider->getValue());
		else
			defaultSettings.dashedValue2 = (unsigned int)slider->getValue();
		return;
	}
}

void LineSettings::handleButtonClick(Button *button) {
	if (button == &roundedType) {
		if (button->getToggleState())
			LineComponent::selected->setLineType(LineComponent::selected->getLineType() | (LineComponent::LineType::rounded));  //select type
		else
			LineComponent::selected->setLineType(LineComponent::selected->getLineType() & ~(LineComponent::LineType::rounded));  //unselect type
		return;
	}
	if (button == &boundBoxType) {
		if (button->getToggleState())
			LineComponent::selected->setLineType(LineComponent::selected->getLineType() | (LineComponent::LineType::boundBox));  //select type
		else
			LineComponent::selected->setLineType(LineComponent::selected->getLineType() & ~(LineComponent::LineType::boundBox));  //unselect type
		return;
	}
	// toggle button is left
	if (dashedTypeButtons.getUnchecked(0)->getToggleState()) //solid type
		LineComponent::selected->setLineType(LineComponent::selected->getLineType() & ~(LineComponent::LineType::dashed));  //unselect type
	else
		LineComponent::selected->setLineType(LineComponent::selected->getLineType() | (LineComponent::LineType::dashed));  //select type

}

void LineSettings::buttonClicked(Button *button) {
	if (!LineComponent::selected) {
		if (button == &roundedType) {
			if (button->getToggleState())
				defaultSettings.type |=  LineComponent::LineType::rounded;  //select type
			else
				defaultSettings.type &=  ~LineComponent::LineType::rounded;  //select type
			return;
		}
		if (button == &boundBoxType) {
			if (button->getToggleState())
				defaultSettings.type |=  LineComponent::LineType::boundBox;  //select type
			else
				defaultSettings.type &=  ~LineComponent::LineType::boundBox;  //select type
			return;
		}
		// toggle button is left
		if (dashedTypeButtons.getUnchecked(0)->getToggleState()) //solid type
			defaultSettings.type &= ~LineComponent::LineType::dashed;  //unselect type
		else
			defaultSettings.type |= LineComponent::LineType::dashed;  //select type
		return;
	}
	if (button == &deleteLine) {
		deleteCurrentLine();
		return;
	}
	startChange();
	handleButtonClick(button);
	endChange();
}

void LineSettings::update() {
	if (LineComponent::selected) {
		lineThickness.setValue(LineComponent::selected->getLineThickness(), NotificationType::dontSendNotification);
		dashedSettings.getUnchecked(0)->setValue(LineComponent::selected->getDashedValue1(), NotificationType::dontSendNotification);
		dashedSettings.getUnchecked(1)->setValue(LineComponent::selected->getDashedValue2(), NotificationType::dontSendNotification);
		int type = LineComponent::selected->getLineType();
		roundedType.setToggleState(type & LineComponent::LineType::rounded, NotificationType::dontSendNotification);
		boundBoxType.setToggleState(type & LineComponent::LineType::boundBox, NotificationType::dontSendNotification);
		dashedTypeButtons.getUnchecked(type & LineComponent::LineType::dashed)->setToggleState(true, NotificationType::dontSendNotification);
		deleteLine.setEnabled(true);
		colourButton.setColour(TextButton::buttonColourId, LineComponent::selected->getColour());
		return;
	}
	int type = defaultSettings.getType();
	lineThickness.setValue(defaultSettings.getLineThickness(), NotificationType::dontSendNotification);
	dashedSettings.getUnchecked(0)->setValue(defaultSettings.getDashedValue1(), NotificationType::dontSendNotification);
	dashedSettings.getUnchecked(1)->setValue(defaultSettings.getDashedValue2(), NotificationType::dontSendNotification);
	roundedType.setToggleState(type & LineComponent::LineType::rounded, NotificationType::dontSendNotification);
	boundBoxType.setToggleState(type & LineComponent::LineType::boundBox, NotificationType::dontSendNotification);
	dashedTypeButtons.getUnchecked(type & LineComponent::LineType::dashed)->setToggleState(true, NotificationType::dontSendNotification);
	deleteLine.setEnabled(false);
	colourButton.setColour(TextButton::buttonColourId, defaultSettings.getColour());
}

void LineSettings::selectListener(CentralComponent *centralComponent) {
	this->centralComponent = centralComponent;
}

void LineSettings::deleteCurrentLine() {
	centralComponent->lineSettingsListener(std::make_pair(LineSettingsState(true, LineComponent::selected), LineSettingsState(false, LineComponent::selected)));
	LineComponent::select(nullptr);
}

LineSettingsState const& LineSettings::getDefaultState() const {
	return defaultSettings;
}

void LineSettings::startChange() {
	if (!LineComponent::selected) return;
	auto &x(LineComponent::selected);
	startSettingChange = LineSettingsState(true, x, x->getLineThickness(), x->getLineType(), x->getColour(), x->getPoint1(), x->getPoint2(), x->getDashedValue1(), x->getDashedValue2());
}

void LineSettings::endChange() {
	if (!LineComponent::selected) return;
	auto &x(LineComponent::selected);
	LineSettingsState endSettingChange(true, x, x->getLineThickness(), x->getLineType(), x->getColour(), x->getPoint1(), x->getPoint2(), x->getDashedValue1(), x->getDashedValue2());
	if (startSettingChange != endSettingChange)
		centralComponent->lineSettingsListener(std::make_pair(startSettingChange, endSettingChange));
}

//==============================================================================
LineSettingsState::LineSettingsState(bool exist, LineComponent *ptr, int lineThickness, int type, Colour colour, Point<int> const &globalPosPoint1, Point<int> const &globalPosPoint2, unsigned int dashedValue1, unsigned int dashedValue2)
	: exist(exist)
	, ptr(ptr)
	, lineThickness(lineThickness)
	, type(type)
	, colour(colour)
	, globalPosPoint1(globalPosPoint1)
	, globalPosPoint2(globalPosPoint2)
	, dashedValue1(dashedValue1)
	, dashedValue2(dashedValue2)
{}

bool LineSettingsState::operator!=(LineSettingsState const &other) const {
	return globalPosPoint1 != other.globalPosPoint1 ||
	       globalPosPoint2 != other.globalPosPoint2 ||
	       exist != other.exist ||
	       ptr != other.ptr ||
	       lineThickness != other.lineThickness ||
	       type != other.type ||
	       colour != other.colour ||
	       dashedValue1 != other.dashedValue1 ||
	       dashedValue2 != other.dashedValue2;
}

bool LineSettingsState::isExist()  const {
	return exist;
}

LineComponent* LineSettingsState::getPtr() const {
	return ptr;
}

int LineSettingsState::getLineThickness() const {
	return lineThickness;
}

int LineSettingsState::getType() const {
	return type;
}

Colour LineSettingsState::getColour() const {
	return colour;
}

Point<int> LineSettingsState::getGlobalPosPoint1() const {
	return globalPosPoint1;
}

Point<int> LineSettingsState::getGlobalPosPoint2() const {
	return globalPosPoint2;
}

unsigned int LineSettingsState::getDashedValue1() const {
	return dashedValue1;
}

unsigned int LineSettingsState::getDashedValue2() const {
	return dashedValue2;
}
