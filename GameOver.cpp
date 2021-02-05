#include "GameOver.hpp"
#include "SFML/Window/Event.hpp"
#include "GamePlay.hpp"

GameOver::GameOver(std::shared_ptr<Context>& context) :
	m_context(context), m_isRetryButtonSelected(true),
	m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
	m_isExitButtonPressed(false)
{

}

GameOver::~GameOver()
{

}

void GameOver::Init()
{
	
	m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_gameOverTitle.setString("Game Over");
	m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2,
		m_gameOverTitle.getLocalBounds().height / 2);
	m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 150.f);

	//play button
	m_retrybutton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_retrybutton.setString("Retry");
	m_retrybutton.setOrigin(m_retrybutton.getLocalBounds().width / 2,
		m_retrybutton.getLocalBounds().height / 2);
	m_retrybutton.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 25.f);
	m_retrybutton.setCharacterSize(20);


	//exit button 
	m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_exitButton.setString("Exit");
	m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
		m_exitButton.getLocalBounds().height / 2);
	m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 + 25.f);
	m_exitButton.setCharacterSize(20);
}
void GameOver::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
			{

				if (!m_isRetryButtonSelected)
				{
					m_isRetryButtonSelected = true;
					m_isExitButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{

				if (m_isRetryButtonSelected)
				{
					m_isRetryButtonSelected = false;
					m_isExitButtonSelected = true;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				m_isRetryButtonPressed = false;
				m_isExitButtonPressed = false;

				if (m_isRetryButtonSelected)
				{
					m_isRetryButtonPressed = true;
				}
				else
				{
					m_isExitButtonPressed = true;
				}
				break;
			}
			default:
			{
				break;
			}

			}
		}
	}
}
void GameOver::Update(sf::Time deltaTime)
{
	if (m_isRetryButtonSelected)
	{
		m_retrybutton.setFillColor(sf::Color::Black);
		m_exitButton.setFillColor(sf::Color::White);
	}
	else
	{
		m_exitButton.setFillColor(sf::Color::Black);
		m_retrybutton.setFillColor(sf::Color::White);
	}

	if (m_isRetryButtonPressed)
	{
		// go to play screen
		m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
	}
	else if (m_isExitButtonPressed)
	{
		m_context->m_window->close();
	}
}
void GameOver::Draw() {
	m_context->m_window->clear(sf::Color::Blue);
	m_context->m_window->draw(m_gameOverTitle);
	m_context->m_window->draw(m_retrybutton);
	m_context->m_window->draw(m_exitButton);
	m_context->m_window->display();

}