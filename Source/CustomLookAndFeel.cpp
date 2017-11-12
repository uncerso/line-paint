/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 3 Nov 2017 11:51:00pm
    Author:  uncerso

  ==============================================================================
*/

#include "CustomLookAndFeel.h"


Font CustomLookAndFeel::getTextButtonFont(TextButton&, int buttonHeight) {
	return Font(fontSize);
}

Font CustomLookAndFeel::getLabelFont(Label&) {
	return Font(fontSize);
}

void CustomLookAndFeel::setFontSize(float fontSize)  noexcept {
	this->fontSize = fontSize;

}

void CustomLookAndFeel::drawGroupComponentOutline(Graphics &g, int width, int height,
                                                  const String &text, const Justification &position,
                                                  GroupComponent &group)
{
	const float textH = fontSize;
	const float indent = 3.0f;
	const float textEdgeGap = 4.0f;
	float cs = 5.0f;

	Font f(textH);

	Path p;
	float x = indent;
	float y = f.getAscent() - 3.0f;
	float w = jmax(0.0f, width - x * 2.0f);
	float h = jmax(0.0f, height - y  - indent);
	cs = jmin(cs, w * 0.5f, h * 0.5f);
	const float cs2 = 2.0f * cs;

	float textW = text.isEmpty() ? 0 : jlimit(0.0f, jmax(0.0f, w - cs2 - textEdgeGap * 2), f.getStringWidth(text) + textEdgeGap * 2.0f);
	float textX = cs + textEdgeGap;

	if (position.testFlags(Justification::horizontallyCentred))
		textX = cs + (w - cs2 - textW) * 0.5f;
	else if (position.testFlags(Justification::right))
		textX = w - cs - textW - textEdgeGap;

	p.startNewSubPath(x + textX + textW, y);
	p.lineTo(x + w - cs, y);

	p.addArc(x + w - cs2, y, cs2, cs2, 0, float_Pi * 0.5f);
	p.lineTo(x + w, y + h - cs);

	p.addArc(x + w - cs2, y + h - cs2, cs2, cs2, float_Pi * 0.5f, float_Pi);
	p.lineTo(x + cs, y + h);

	p.addArc(x, y + h - cs2, cs2, cs2, float_Pi, float_Pi * 1.5f);
	p.lineTo(x, y + cs);

	p.addArc(x, y, cs2, cs2, float_Pi * 1.5f, float_Pi * 2.0f);
	p.lineTo(x + textX, y);

	const float alpha = group.isEnabled() ? 1.0f : 0.5f;

	g.setColour(group.findColour(GroupComponent::outlineColourId)
	            .withMultipliedAlpha(alpha));

	g.strokePath(p, PathStrokeType(2.0f));

	g.setColour(group.findColour(GroupComponent::textColourId)
	            .withMultipliedAlpha(alpha));
	g.setFont(f);
	g.drawText(text,
	           roundToInt(x + textX), 0,
	           roundToInt(textW),
	           roundToInt(textH),
	           Justification::centred, true);
}
