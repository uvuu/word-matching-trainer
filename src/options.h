#ifndef OPTIONS_H
#define OPTIONS_H

#include <QObject>

class Options : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int questionTime READ getQuestionTime WRITE setQuestionTime NOTIFY questionTimeChanged)
    Q_PROPERTY(int answerTime READ getAnswerTime WRITE setAnswerTime NOTIFY answerTimeChanged)
    Q_PROPERTY(int exerciseIndex READ getExerciseIndex WRITE setExerciseIndex NOTIFY exerciseIndexChanged)

public:
    explicit Options(QObject *parent = nullptr);

    int getQuestionTime() const;
    void setQuestionTime(int time);
    int getAnswerTime() const;
    void setAnswerTime(int time);
    int getExerciseIndex() const;
    void setExerciseIndex(int exerciseIndex);

private:
    int m_questionTime{1000}; // ms
    int m_answerTime{700}; // ms
    int m_exerciseIndex{0};

signals:
    void questionTimeChanged();
    void answerTimeChanged();
    void exerciseIndexChanged();
};

#endif // OPTIONS_H
