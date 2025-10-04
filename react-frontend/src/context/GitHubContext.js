import React, { createContext, useContext, useState, useCallback } from 'react';
import axios from 'axios';
import toast from 'react-hot-toast';

const GitHubContext = createContext();

export const useGitHub = () => {
  const context = useContext(GitHubContext);
  if (!context) {
    throw new Error('useGitHub must be used within a GitHubProvider');
  }
  return context;
};

const GITHUB_API_BASE = 'https://api.github.com';
const REPO_OWNER = 'Pradeepsingh61';
const REPO_NAME = 'DSA_Code';
const GITHUB_RAW_BASE = `https://raw.githubusercontent.com/${REPO_OWNER}/${REPO_NAME}/main`;

export const GitHubProvider = ({ children }) => {
  const [loading, setLoading] = useState(false);
  const [repoData, setRepoData] = useState(null);
  const [contributors, setContributors] = useState([]);

  // Fetch repository information
  const fetchRepoInfo = useCallback(async () => {
    try {
      setLoading(true);
      const response = await axios.get(`${GITHUB_API_BASE}/repos/${REPO_OWNER}/${REPO_NAME}`);
      setRepoData(response.data);
      return response.data;
    } catch (error) {
      console.error('Error fetching repo info:', error);
      toast.error('Failed to fetch repository information');
      return null;
    } finally {
      setLoading(false);
    }
  }, []);

  // Fetch contributors
  const fetchContributors = useCallback(async () => {
    try {
      const response = await axios.get(`${GITHUB_API_BASE}/repos/${REPO_OWNER}/${REPO_NAME}/contributors`);
      setContributors(response.data);
      return response.data;
    } catch (error) {
      console.error('Error fetching contributors:', error);
      return [];
    }
  }, []);

  // Fetch file content from GitHub
  const fetchFileContent = useCallback(async (filePath) => {
    try {
      setLoading(true);
      const response = await axios.get(`${GITHUB_RAW_BASE}/${filePath}`);
      return response.data;
    } catch (error) {
      console.error('Error fetching file content:', error);
      toast.error('Failed to fetch file content');
      return null;
    } finally {
      setLoading(false);
    }
  }, []);

  // Fetch directory contents
  const fetchDirectoryContents = useCallback(async (path = '') => {
    try {
      setLoading(true);
      const response = await axios.get(`${GITHUB_API_BASE}/repos/${REPO_OWNER}/${REPO_NAME}/contents/${path}`);
      return response.data;
    } catch (error) {
      console.error('Error fetching directory contents:', error);
      return [];
    } finally {
      setLoading(false);
    }
  }, []);

  // Search repository files
  const searchFiles = useCallback(async (query, language = '') => {
    try {
      setLoading(true);
      let searchQuery = `${query} repo:${REPO_OWNER}/${REPO_NAME}`;
      if (language) {
        searchQuery += ` language:${language}`;
      }
      
      const response = await axios.get(`${GITHUB_API_BASE}/search/code`, {
        params: { q: searchQuery }
      });
      return response.data.items;
    } catch (error) {
      console.error('Error searching files:', error);
      return [];
    } finally {
      setLoading(false);
    }
  }, []);

  // Get file URL for GitHub
  const getFileUrl = useCallback((filePath) => {
    return `https://github.com/${REPO_OWNER}/${REPO_NAME}/blob/main/${filePath}`;
  }, []);

  // Get raw file URL
  const getRawFileUrl = useCallback((filePath) => {
    return `${GITHUB_RAW_BASE}/${filePath}`;
  }, []);

  // Fetch repository statistics
  const fetchRepoStats = useCallback(async () => {
    try {
      const [repoInfo, contributorsData] = await Promise.all([
        fetchRepoInfo(),
        fetchContributors()
      ]);

      return {
        stars: repoInfo?.stargazers_count || 0,
        forks: repoInfo?.forks_count || 0,
        contributors: contributorsData?.length || 0,
        lastUpdated: repoInfo?.updated_at || null
      };
    } catch (error) {
      console.error('Error fetching repo stats:', error);
      return {
        stars: 0,
        forks: 0,
        contributors: 0,
        lastUpdated: null
      };
    }
  }, [fetchRepoInfo, fetchContributors]);

  const value = {
    loading,
    repoData,
    contributors,
    fetchRepoInfo,
    fetchContributors,
    fetchFileContent,
    fetchDirectoryContents,
    searchFiles,
    getFileUrl,
    getRawFileUrl,
    fetchRepoStats,
    REPO_OWNER,
    REPO_NAME
  };

  return (
    <GitHubContext.Provider value={value}>
      {children}
    </GitHubContext.Provider>
  );
};
