/*
 *  problemMathFour.cpp
 *
 *  Created by Ryan Raffa on 4/25/13.
 *
 */

#include "problemMathFour.h"




////////////////////////////////////////////////////////////////////
//      RESET                                                     //
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
problemMathFour::~problemMathFour() {

    delete create;
    delete reflect;
    delete present;

}



////////////////////////////////////////////////////////////////////
//      SETUP                                                     //
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
problemMathFour::problemMathFour() {
        
 
    theText = "Which value of x is the solution of the following equation?";
    
//-----------------------------------------------    
//setup math problem one
    
    create = new uiCreate(theText);
    reflect = new uiReflect;
    present = new uiPresent;
    
    ofPoint pos;
    ofPoint size;
    ofPoint offSet;
    ofColor color;
    questionButtonImage.loadImage("images/ui/glyphicons_194_circle_question_mark.png");
    
    size.set(questionButtonImage.getWidth()+20, questionButtonImage.getHeight()+20);
    pos.set(ofGetWidth()-45, 0);
    offSet.set(15, 32);
    color.set(170, 170, 170);
    questionButton.setup(pos, size, color);
    
    ofPoint posTwo;
    posTwo.set(46, 0);
    size.set(311, 46);
    color.set(200, 52, 70, 255);
    createButton.setup(posTwo, size, offSet, "1. Create", color);
    
    ofPoint posThree;
    posThree.set(357, 0);
    color.set(68, 116, 176, 255);
    reflectButton.setup(posThree, size, offSet, "2. Reflect", color);
    
    ofPoint posFour;
    posThree.set(668, 0);
    color.set(230, 224, 47, 255);
    presentButton.setup(posThree, size, offSet, "3. Present", color);
    
    navStateCreate = true;
    navStateReflect = false;
    navStatePresent = false;
    navStateQuestion = false;
    
    equation.loadImage("images/equation.png");
    
//-----------------------------------------------
//poor man's feedback
    
    feedbackBrickPos.set(50, 46);
    
    printf(" problemMathFour Setup ended \n ");

}


////////////////////////////////////////////////////////////////////
//      UPDATE                                                    //
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------        
void problemMathFour::update() {
    
    
//-----------------------------------------------
//NAV state is sorted out
    
    if (createButton.selected) {
        navStateReflect = false;
        navStatePresent = false;
        navStateQuestion = false;
        navStateCreate = true;
        createButton.selected=false;
    }
    
    if (reflectButton.selected) {
        navStateCreate = false;
        navStatePresent = false;
        navStateQuestion = false;
        navStateReflect = true;
        reflectButton.selected=false;
        
        //set value of drawing
        reflect->setPoints(create->drawThese);
    }
    
    if (presentButton.selected) {
        navStateCreate = false;
        navStateReflect = false;
        navStateQuestion = false;
        navStatePresent = true;
        presentButton.selected=false;

        //set value of drawing
        present->setPoints(create->drawThese, reflect->theFlagStates);

    }
    
    if (questionButton.selected) {        
        navStateCreate = false;
        navStateReflect = false;
        navStatePresent = false;
        navStateQuestion = true;
        questionButton.selected=false;
    }
    
//-----------------------------------------------
//What is done based on NAV state

    if (navStateCreate) create->update();
    if (navStateReflect) reflect->update();
    if (navStatePresent) present->update();

//-----------------------------------------------
//poor man's feedback

    if (navStateCreate) {
        distX = createButton.pos.x - feedbackBrickPos.x;
        feedbackBrickPos.x += distX/8.0;
    }
    
    if (navStateReflect) {
        distX = reflectButton.pos.x - feedbackBrickPos.x;
        feedbackBrickPos.x += distX/8.0;
    }
    
    if (navStatePresent) {
        distX = presentButton.pos.x - feedbackBrickPos.x;
        feedbackBrickPos.x += distX/8.0;
    }

    if (navStateQuestion) {
        distX = questionButton.pos.x - feedbackBrickPos.x;
        feedbackBrickPos.x += distX/8.0;
    }


}


////////////////////////////////////////////////////////////////////
//      DRAW                                                      //
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
void problemMathFour::draw(ofTrueTypeFont& basicFont) {

//-----------------------------------------------
//poor man's feedback
    
    ofSetLineWidth(1.0);

    ofRect(feedbackBrickPos.x, feedbackBrickPos.y, 311, 5);
    
//-----------------------------------------------
//actual state
    
    if (navStateCreate) create->draw(basicFont);
    if (navStateReflect) reflect->draw(basicFont);
    if (navStatePresent) present->draw(basicFont);
    
//-----------------------------------------------
//The Question

    ofSetColor(0, 0, 0);
    basicFont.drawString(theText, 10, 100);
    
    ofEnableAlphaBlending();
    ofSetColor(255, 255, 255);
    equation.draw(15,125);
    ofDisableAlphaBlending();

    
//-----------------------------------------------
//Feedback
    
//    if (navStateCreate) basicFont.drawString("create selected", ofGetWidth()/2, 60);
//    if (navStateReflect) basicFont.drawString("reflect selected", ofGetWidth()/2, 60);
//    if (navStatePresent) basicFont.drawString("present selected", ofGetWidth()/2, 60);
//    if (navStateQuestion) basicFont.drawString("question selected", ofGetWidth()/2, 60);

//-----------------------------------------------
//Button UI

    createButton.draw(basicFont);
    reflectButton.draw(basicFont);
    presentButton.draw(basicFont);
    questionButton.draw(basicFont);
    
    ofEnableAlphaBlending();
    questionButtonImage.draw(ofGetWidth()-35, 10);
    ofDisableAlphaBlending();
    
}


////////////////////////////////////////////////////////////////////
//      TOUCH                                                     //
////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
void problemMathFour::touchingDown(ofTouchEventArgs &touch) {

    createButton.touchingDown(touch);
    reflectButton.touchingDown(touch);
    presentButton.touchingDown(touch);
    questionButton.touchingDown(touch);
    
    if (navStateCreate) create->touchingDown(touch);
    if (navStateReflect) reflect->touchingDown(touch);
    if (navStatePresent) present->touchingDown(touch);
    
}

//------------------------------------------------------------------
void problemMathFour::touchingMove(ofTouchEventArgs &touch) {
    
    createButton.touchingMove(touch);
    reflectButton.touchingMove(touch);
    presentButton.touchingMove(touch);
    questionButton.touchingMove(touch);

    if (navStateCreate) create->touchingMove(touch);
    if (navStateReflect) reflect->touchingMove(touch);
    if (navStatePresent) present->touchingMove(touch);
    
}

//------------------------------------------------------------------
void problemMathFour::touchingUp(ofTouchEventArgs &touch) {
    
    createButton.touchingUp(touch);
    reflectButton.touchingUp(touch);
    presentButton.touchingUp(touch);
    questionButton.touchingUp(touch);

    if (navStateCreate) create->touchingUp(touch);
    if (navStateReflect) reflect->touchingUp(touch);
    if (navStatePresent) present->touchingUp(touch);
    
}

//------------------------------------------------------------------
void problemMathFour::doubleTap(ofTouchEventArgs &touch) {

    createButton.doubleTap(touch);
    reflectButton.doubleTap(touch);
    presentButton.doubleTap(touch);
    questionButton.doubleTap(touch);

    if (navStateCreate) create->doubleTap(touch);
    if (navStateReflect) reflect->doubleTap(touch);
    if (navStatePresent) present->doubleTap(touch);
    
}

    

