#include <Processing/EventManager.hpp>
//CONSTRUCTORS

//DESTRUCTORS

//METHODS
void EventManager::closeGame()
{
	dLink->runGraphics = false;
	dLink->runPhysics = false;
	dLink->runModules = false;
	GMutex.unlock();
	gThread->wait();
	pThread->wait();
	mThread->wait();
	GMutex.lock();
	dLink->renderWindow->close();
}
void EventManager::handleEvent(sf::Event *_event)
{
	//Self-Management
	mLink->handleEvent(_event);
	if (_event->type == sf::Event::MouseMoved)
	{
		if (dLink->guiMode)
			return;
		dLink->localCtrl.targetPoint = Vector(dLink->renderWindow->mapPixelToCoords(sf::Mouse::getPosition(*dLink->renderWindow), dLink->gameView));
	}
	else if (_event->type == sf::Event::KeyPressed && _event->key.code == sf::Keyboard::Escape || _event->type == sf::Event::Closed)
	{
		closeGame();
		return;
	}
	else if (_event->type == sf::Event::Resized)
	{
		dLink->gameView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dLink->renderWindow->getSize().x), static_cast<float>(dLink->renderWindow->getSize().y)));
		dLink->gameView.move(-(dLink->renderWindow->getSize().x / 2.0), -(dLink->renderWindow->getSize().y / 2.0));
		dLink->renderWindow->setView(dLink->gameView);
		dLink->guiView = sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(dLink->renderWindow->getSize().x), static_cast<float>(dLink->renderWindow->getSize().y)));
		dLink->renderWindow->setView(dLink->guiView);
		return;
	}
	return;
}
void EventManager::handleSoftEvent(std::list<std::string> _args)
{
	// to the plugins
	eventBuffer.push_back(_args);
	//Handling events for the game
	if (*_args.begin() == "action")
	{
		_args.pop_front();
		dLink->localCtrl.analyzeAction(_args);
		if (*_args.begin() == "modeSwitch")
		{
			dLink->guiMode = !dLink->guiMode;
		}
		if (!dLink->guiMode)
		{
			if (*_args.begin() == "zoomOut")
			{
				float _time = 0.3f;
				float _zoomFactor = 1.3f;
				float _updateRate = 30.0f;

				int _jumps = _time*_updateRate;
				float _jumpStep = pow(_zoomFactor, 1.0f / _jumps);

				for (float i = 0.0f; i <= _time; i += 1.0 / _updateRate)
				{
					std::list< std::string > x;
					x.push_back("delay");
					x.push_back(util::toString(i*1000.0));
					x.push_back("zoom");
					x.push_back(util::toString(_jumpStep));
					dLink->pushTask(x);
				}
			}
			else if (*_args.begin() == "zoomIn")
			{
				float _time = 0.3f;
				float _zoomFactor = 0.7f;
				float _updateRate = 30.0f;

				int _jumps = _time*_updateRate;
				float _jumpStep = pow(_zoomFactor, 1.0f / _jumps);

				for (float i = 0.0f; i <= _time; i += 1.0 / _updateRate)
				{
					std::list< std::string > x;
					x.push_back("delay");
					x.push_back(util::toString(i*1000.0));
					x.push_back("zoom");
					x.push_back(util::toString(_jumpStep));
					dLink->pushTask(x);
				}
			}
		}
	}
}
void EventManager::handleTask(std::list<std::string> _args)
{
	// to the plugins
	taskBuffer.push_back(_args);

	if (*_args.begin() == "debug")
	{
		_args.pop_front();
		if (*_args.begin() == "countReset")
		{
			while (dLink->debug.eventCounts.size() > dLink->settings.eventtaskMeanAmount)
			{
				dLink->debug.eventCounts.pop_front();
			}
			while (dLink->debug.taskCounts.size() > dLink->settings.eventtaskMeanAmount)
			{
				dLink->debug.taskCounts.pop_front();
			}
			dLink->debug.eventCounts.push_back(dLink->debug.eventCount);
			dLink->debug.taskCounts.push_back(dLink->debug.taskCount);

			dLink->debug.eventCount = 0;
			dLink->debug.taskCount = 0;

			std::list<std::string> x;
			x.push_back("delay");
			x.push_back(util::toString(dLink->settings.countResetInterval * 1000));
			x.push_back("debug");
			x.push_back("countReset");
			dLink->pushTask(x);
		}
	}
	else if (*_args.begin() == "_CORE")
	{
		_args.pop_front();
		if (*_args.begin() == "quitGame")
		{
			closeGame();
			return;
		}
	}
	else if (*_args.begin() == "zoom")
	{
		_args.pop_front();
		float factor = util::toFloat(*_args.begin());
		dLink->gameView.zoom(factor);
	}
}
void EventManager::processEvent(sf::Event *_event)
{
	handleEvent(_event);
	guiLink->handleEvent(_event);
}
void EventManager::processSoftEvent(std::list<std::string> _args)
{
	handleSoftEvent(_args);
	guiLink->handleSoftEvent(_args);
}
void EventManager::processTask(std::list<std::string> _args)
{
	handleTask(_args);
}
