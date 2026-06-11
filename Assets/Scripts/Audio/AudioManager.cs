using UnityEngine;
using System.Collections.Generic;

public class AudioManager : MonoBehaviour
{
    [Header("音頻源")]
    [SerializeField] private AudioSource trainSoundSource;
    [SerializeField] private AudioSource announcementSource;
    [SerializeField] private AudioSource ambientSource;
    [SerializeField] private AudioSource musicSource;
    
    [Header("音效資源")]
    [SerializeField] private List<AudioClip> trainAccelerationSounds;
    [SerializeField] private List<AudioClip> trainBrakingSounds;
    [SerializeField] private List<AudioClip> doorSounds;
    [SerializeField] private List<AudioClip> stationAnnouncements;
    [SerializeField] private List<AudioClip> ambientSounds;
    
    private Dictionary<string, AudioClip> audioDatabase = new Dictionary<string, AudioClip>();
    private bool japaneseAnnouncements = true;

    private void Start()
    {
        InitializeAudioDatabase();
    }

    private void InitializeAudioDatabase()
    {
        // 初始化音頻資料庫
        foreach (var clip in trainAccelerationSounds)
        {
            if (clip != null)
                audioDatabase[clip.name] = clip;
        }
    }

    public void PlayTrainAccelerationSound()
    {
        if (trainAccelerationSounds.Count > 0)
        {
            AudioClip clip = trainAccelerationSounds[Random.Range(0, trainAccelerationSounds.Count)];
            trainSoundSource.PlayOneShot(clip);
        }
    }

    public void PlayTrainBrakingSound()
    {
        if (trainBrakingSounds.Count > 0)
        {
            AudioClip clip = trainBrakingSounds[Random.Range(0, trainBrakingSounds.Count)];
            trainSoundSource.PlayOneShot(clip);
        }
    }

    public void PlayDoorOpenSound()
    {
        if (doorSounds.Count > 0)
        {
            AudioClip clip = doorSounds[0];
            trainSoundSource.PlayOneShot(clip);
        }
    }

    public void PlayDoorCloseSound()
    {
        if (doorSounds.Count > 1)
        {
            AudioClip clip = doorSounds[1];
            trainSoundSource.PlayOneShot(clip);
        }
    }

    public void PlayStationAnnouncement(string stationName, bool japanese = true)
    {
        // 播放車站播報
        Debug.Log($"播放車站播報: {stationName} ({(japanese ? "日語" : "英語")})");
        
        if (stationAnnouncements.Count > 0)
        {
            AudioClip clip = stationAnnouncements[Random.Range(0, stationAnnouncements.Count)];
            announcementSource.PlayOneShot(clip);
        }
    }

    public void PlayAmbientSound(string soundType)
    {
        if (ambientSounds.Count > 0)
        {
            AudioClip clip = ambientSounds[Random.Range(0, ambientSounds.Count)];
            ambientSource.PlayOneShot(clip);
        }
    }

    public void PlayBackgroundMusic(AudioClip musicClip)
    {
        if (musicClip != null)
        {
            musicSource.clip = musicClip;
            musicSource.loop = true;
            musicSource.Play();
        }
    }

    public void StopBackgroundMusic()
    {
        musicSource.Stop();
    }

    public void SetVolume(AudioType type, float volume)
    {
        volume = Mathf.Clamp01(volume);
        
        switch (type)
        {
            case AudioType.Train:
                trainSoundSource.volume = volume;
                break;
            case AudioType.Announcement:
                announcementSource.volume = volume;
                break;
            case AudioType.Ambient:
                ambientSource.volume = volume;
                break;
            case AudioType.Music:
                musicSource.volume = volume;
                break;
        }
    }

    public void SetLanguage(bool japanese)
    {
        japaneseAnnouncements = japanese;
    }
}

public enum AudioType
{
    Train,
    Announcement,
    Ambient,
    Music
}
