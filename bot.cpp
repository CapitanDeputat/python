//������� �������� ������� �������� ����(��������� �� ������ � ������)
/*
	bot - ������ �� ����
	enemy - ��������� ����(�����)
	apple -  ������
*/
//���������� ���� ���� ��� ���������� � �����
bool hardMode(Snake* bot, Snake enemy, Apple apple)
{
	
	return res;
}
//������� �������� ������� �������� ����(���������� � ������, ������� �� ������ �����)
/*
	bot - ������ �� ����
	enemy - ��������� ����(�����)
	apple -  ������
*/
//���������� ���� ���� ��� ���������� � �����
bool normalMode(Snake* bot, Snake enemy, Apple apple)
{

}


//������� �������� ����� ������� �������� ����(���������� � ������)
/*
	bot - ������ �� ����
	enemy - ��������� ����(�����)
	apple -  ������
*/
//���������� ���� ���� ��� ���������� � �����
bool goToApple(Snake* bot, Snake enemy, Apple apple)
{

	return res;
}

//������� �������� �������� ����
/*
	bot - ������ �� ����
	level - ������� ���������
	enemy - ��������� ����(�����)
	apple -  ������
*/
//���������� ���� ���� ��� ���������� � �����
bool chooseMove(Snake* bot, std::string level, Snake enemy, Apple apple)
{
	bool result = false;
	if (level == "insane")
		result = hardMode(bot, enemy, apple);
	if (level == "medium")
		result = normalMode(bot, enemy, apple);
	if (level == "easy")
		result = goToApple(bot, enemy, apple);

	if (enemy.collideWithSnake(bot->getSnakeX(), bot->getSnakeY()))
		result = false;
	return result;
}
