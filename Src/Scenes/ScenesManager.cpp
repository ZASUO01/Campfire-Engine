#include "ScenesManager.h"
#include "CampfireEngine/Scenes/Scene.h"

ScenesManager::ScenesManager(GameBase* mGame)
:mCurrentScene(nullptr)
,mNextScene(nullptr)
,mState(State::IDLE)
,mGame{mGame}
{}

ScenesManager::~ScenesManager() {
    mLoadingThread.request_stop();

    if (mLoadingThread.joinable()) {
        mLoadingThread.join();
    }

    if (mCurrentScene) {
        mCurrentScene->OnExit(mGame);
    }

    if (mNextScene) {
        mNextScene->OnExit(mGame);
    }
}

void ScenesManager::SetCurrentScene(std::unique_ptr<Scene> newScene) {
    if (mState.load() == State::LOADING || mState.load() == State::LOADED) {
        return;
    }

    mNextScene = std::move(newScene);
    mState.store(State::LOADING);

    mLoadingThread = std::jthread([this](const std::stop_token& st) {
        if (mNextScene) {
            mNextScene->InternalInit(st, this);
        }

        if (st.stop_requested()) {
            mState.store(State::IDLE);
            return;
        }

        mState.store(State::LOADED);
    });
}

void ScenesManager::UpdateState() {
    if (mState.load() != State::LOADED) {
        return;
    }

    if (mLoadingThread.joinable()) {
        mLoadingThread.detach();
    }

    if (mCurrentScene) {
        mCurrentScene->OnExit(mGame);
        mCurrentScene.reset();
    }

    if (mNextScene) {
        mNextScene->OnPostInit(this, mGame);
    }

    mCurrentScene = std::move(mNextScene);
    mState.store(State::READY);
}
